#include "putty.h"
#include "terminal.h"
#include <windows.h>
#include <time.h>

void xyz_updateMenuItems(Terminal *term);

void xyz_ReceiveInit(Terminal *term);
int xyz_ReceiveData(Terminal *term, const u_char *buffer, int len);
static int xyz_SpawnProcess(Terminal *term, const char *incommand, const char *inparams);

// HERE
#include <stdio.h>

#define DEBUG 0

void dbg(const char *msg) {
  if (DEBUG == 1) {
    FILE *f;
    f = fopen("test.log","a");
    fprintf(f,msg);
    fclose(f);
  }
}
// HERE

#define MAX_UPLOAD_FILES 512

#define PIPE_SIZE (64*1024)

struct zModemInternals {
	PROCESS_INFORMATION pi;
	HANDLE read_stdout;
	HANDLE read_stderr;
	HANDLE write_stdin;
};

static int IsWinNT()
{
	dbg("IsWinNt\n");
	OSVERSIONINFO osv;
	osv.dwOSVersionInfoSize = sizeof(osv);
	GetVersionEx(&osv);
	return (osv.dwPlatformId == VER_PLATFORM_WIN32_NT);
}

void xyz_Done(Terminal *term)
{
	dbg("xyzDone\n");
	if (term->xyz_transfering != 0) {
		term->xyz_transfering = 0;
	        dbg("Transfer done\n");
		xyz_updateMenuItems(term);
	        dbg("update items\n");

		if (term->xyz_Internals) {
	                dbg("xyz internals\n");
			DWORD exitcode = 0;
			CloseHandle(term->xyz_Internals->write_stdin);
			Sleep(500);
			CloseHandle(term->xyz_Internals->read_stdout);
			CloseHandle(term->xyz_Internals->read_stderr);
			GetExitCodeProcess(term->xyz_Internals->pi.hProcess,&exitcode);      //while the process is running
			if (exitcode == STILL_ACTIVE) {
				TerminateProcess(term->xyz_Internals->pi.hProcess, 0);
			}
			sfree(term->xyz_Internals);
			term->xyz_Internals = NULL;
	                dbg("done\n");
		}
	}
}

//static int xyz_Check(Backend *back, void *backhandle, Terminal *term, int outerr);
//static int xyz_Check(Backend *back, Seat *seat, Terminal *term, int outerr);
static int xyz_Check(Backend *back, void *backhandle, Terminal *term, int outerr);

int xyz_Process(Backend *back, void *backhandle, Terminal *term)
{
	//dbg("xyzProcess\n");
	return xyz_Check(back, backhandle, term, 0) + xyz_Check(back, backhandle, term, 1);
}

//static int xyz_Check(Backend *back, void *backhandle, Terminal *term, int outerr)
//static int xyz_Check(Backend *backend, Terminal *term, int outerr)
static int xyz_Check(Backend *back, void *backhandle, Terminal *term, int outerr)
{
	//dbg("xyzCheck\n");
	DWORD exitcode = 0;
	DWORD bread, avail;
	char buf[1024];
	HANDLE h;

	if (!term->xyz_transfering) {
	        //dbg("not transfering\n");
		return 0;
	}

	if (outerr) {
		h = term->xyz_Internals->read_stdout;
	} else {
		h = term->xyz_Internals->read_stderr;
	}

	bread = 0;
	PeekNamedPipe(h,buf,1,&bread,&avail,NULL);
	//check to see if there is any data to read from stdout
	if (bread != 0)
	{
	        dbg("got bread\n");
		while (1)
		{
			bread = 0;
		
			PeekNamedPipe(h,buf,1,&bread,&avail,NULL);
			if (bread == 0)
				return 0;

			if (ReadFile(h,buf,sizeof(buf),&bread,NULL))  { //read the stdout pipe
				if (bread) {
#if 0
					char *buffer;
					int len;
					
					buffer = buf;
					len = bread;
					if (0)
					{
						char *debugbuff;
						char *bb, *p;
						int i;
						
						debugbuff = _alloca(len*3+128);
						debugbuff[0] = 0;
						bb = debugbuff;
						p = buffer;
						bb += sprintf(bb, "R: %8d   ", time(NULL));
						for(i=0; i < len; i++) {
							bb += sprintf(bb, "%2x ", *p++);
						}
						bb += sprintf(bb, "\n");
						
						OutputDebugString(debugbuff);
					} else {
						char *debugbuff;
						debugbuff = _alloca(len+128);
						memcpy(debugbuff, buffer, len);
						debugbuff[len] = 0;
						if (outerr) {
							strcat(debugbuff, "<<<<<<<\n");
						} else {
							strcat(debugbuff, "*******\n");
						}
						OutputDebugString(debugbuff);
					}
#endif
					if (outerr) {
				          backend_send(back, buf, bread);
				        } else {
					  from_backend(term, 1, buf, bread);
				        }
					continue;
				}
			}
			// EOF/ERROR
			xyz_Done(term);
			return 1;
		}
		return 1;
	}
	
	GetExitCodeProcess(term->xyz_Internals->pi.hProcess,&exitcode);
	if (exitcode != STILL_ACTIVE) {
	        dbg("Check Done\n");
		xyz_Done(term);
		return 1;
	}

	return 0;
}

void xyz_ReceiveInit(Terminal *term)
{

	dbg("xyzReceiveInit\n");
        char *rzcommand;
        char *rzoptions;

        rzcommand = conf_get_str(term->conf, CONF_rzcommand);
        rzoptions = conf_get_str(term->conf, CONF_rzoptions);

	if (xyz_SpawnProcess(term, rzcommand, rzoptions) == 0) {
	        dbg("xyzSpawnOK\n");
		term->xyz_transfering = 1;
	}
}

void xyz_StartSending(Terminal *term)
{

	dbg("xyzStartSending\n");
        char *szcommand;
        char *szoptions;

        szcommand = conf_get_str(term->conf, CONF_szcommand);
        szoptions = conf_get_str(term->conf, CONF_szoptions);


	OPENFILENAME fn;
	char filenames[32000];
	BOOL res;

	memset(&fn, 0, sizeof(fn));
	memset(filenames, 0, sizeof(filenames));
	fn.lStructSize = sizeof(fn);
	fn.lpstrFile = filenames;
        // the missing -1 was causing a crash on very long selections
	fn.nMaxFile = sizeof(filenames)-1; 
	fn.lpstrTitle = "Select files to upload...";
	fn.Flags = OFN_ALLOWMULTISELECT | OFN_CREATEPROMPT | OFN_ENABLESIZING | OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY | OFN_PATHMUSTEXIST;

	dbg("bf GetOpenFileName\n");
	//res = GetOpenFileName(&fn);
	res = request_file(NULL, &fn, false, false);

	if (res)
	{
		char sz_full_params[32767];
		char *p, *curparams;
		p = filenames;

		curparams = sz_full_params;
		sz_full_params[0] = 0;

		curparams += sprintf(curparams, "%s", szoptions);

		if (*(p+strlen(filenames)+1)==0) {
			sprintf(curparams, " \"%s\"", filenames);
		} else {
			for (;;) {
				p=p+strlen(p)+1;
				if (*p==0)
					break;
				curparams += sprintf(curparams, " \"%s\\%s\"", filenames, p);
			}
		}
		if (xyz_SpawnProcess(term, szcommand, sz_full_params) == 0) {
	                dbg("transferring = 1\n");
			term->xyz_transfering = 1;
		}
	}
}

void xyz_Cancel(Terminal *term)
{
	dbg("xyz_Cancel\n");
	xyz_Done(term);
}

static int xyz_SpawnProcess(Terminal *term, const char *incommand, const char *inparams)
{
	dbg("xyzSpawnProcess\n");
	STARTUPINFO si;
	SECURITY_ATTRIBUTES sa;
	SECURITY_DESCRIPTOR sd;               //security information for pipes
	
	HANDLE read_stdout, read_stderr, write_stdin, newstdin, newstdout, newstderr; //pipe handles
        char *zdownloaddir;

        zdownloaddir = conf_get_str(term->conf, CONF_zdownloaddir);
	
	
	term->xyz_Internals = (struct zModemInternals *)smalloc(sizeof(struct zModemInternals));
	memset(term->xyz_Internals, 0, sizeof(struct zModemInternals));

	if (IsWinNT())        //initialize security descriptor (Windows NT)
	{
		InitializeSecurityDescriptor(&sd,SECURITY_DESCRIPTOR_REVISION);
		SetSecurityDescriptorDacl(&sd, TRUE, NULL, FALSE);
		sa.lpSecurityDescriptor = &sd;
	}
	else sa.lpSecurityDescriptor = NULL;
	sa.nLength = sizeof(SECURITY_ATTRIBUTES);
	sa.bInheritHandle = TRUE;         //allow inheritable handles
	
	dbg("Create stdin Pipe\n");
	if (!CreatePipe(&newstdin,&write_stdin,&sa,PIPE_SIZE))   //create stdin pipe
	{
		return 1;
	}
	dbg("Create stdout Pipe\n");
	if (!CreatePipe(&read_stdout,&newstdout,&sa,PIPE_SIZE))  //create stdout pipe
	{
		CloseHandle(newstdin);
		CloseHandle(write_stdin);
		return 1;
	}
	dbg("Create stderr Pipe\n");
	if (!CreatePipe(&read_stderr,&newstderr,&sa,PIPE_SIZE))  //create stdout pipe
	{
		CloseHandle(newstdin);
		CloseHandle(write_stdin);
		CloseHandle(newstdout);
		CloseHandle(read_stdout);
		return 1;
	}

	
	dbg("get handle\n");
	GetStartupInfo(&si);      //set startupinfo for the spawned process
				  /*
				  The dwFlags member tells CreateProcess how to make the process.
				  STARTF_USESTDHANDLES validates the hStd* members. STARTF_USESHOWWINDOW
				  validates the wShowWindow member.
	*/
	si.dwFlags = STARTF_USESTDHANDLES|STARTF_USESHOWWINDOW;
	si.wShowWindow = SW_HIDE;
	si.hStdOutput = newstdout;
	si.hStdError = newstderr;     //set the new handles for the child process
	si.hStdInput = newstdin;

	
	//system
	dbg("duplicate stdout\n");
	if (!DuplicateHandle(GetCurrentProcess(), read_stdout, GetCurrentProcess(), &term->xyz_Internals->read_stdout, 0, FALSE, DUPLICATE_SAME_ACCESS))
	{
		CloseHandle(newstdin);
		CloseHandle(write_stdin);
		CloseHandle(newstdout);
		CloseHandle(read_stdout);
		CloseHandle(newstderr);
		CloseHandle(read_stderr);
		return 1;
	}

	CloseHandle(read_stdout);

	dbg("duplicate stderr\n");
	if (!DuplicateHandle(GetCurrentProcess(), read_stderr, GetCurrentProcess(), &term->xyz_Internals->read_stderr, 0, FALSE, DUPLICATE_SAME_ACCESS))
	{
		CloseHandle(newstdin);
		CloseHandle(newstdout);
		CloseHandle(read_stdout);
		CloseHandle(write_stdin);
		CloseHandle(newstderr);
		CloseHandle(read_stderr);
		return 1;
	}

	CloseHandle(read_stderr);

	dbg("duplicate write stdin\n");
	if (!DuplicateHandle(GetCurrentProcess(), write_stdin, GetCurrentProcess(), &term->xyz_Internals->write_stdin, 0, FALSE, DUPLICATE_SAME_ACCESS))
	{
		CloseHandle(newstdin);
		CloseHandle(write_stdin);
		CloseHandle(newstdout);
		CloseHandle(term->xyz_Internals->read_stdout);
		CloseHandle(newstderr);
		CloseHandle(term->xyz_Internals->read_stderr);
		return 1;
	}

	CloseHandle(write_stdin);
	
	dbg("spawn the child process\n");
	//spawn the child process
	{
		char params[1204];
		const char *p;

		p = incommand + strlen(incommand);
		while (p != incommand) {
			if (*p == '\\' || *p == ' ') { // no space in name either
				p++;
				break;
			}
			p--;
		}
		sprintf(params, "%s %s", p, inparams);
	        dbg(incommand);
	        dbg("\n");
                dbg(params);
	        dbg("\n");
		if (!CreateProcess(incommand,params,NULL, NULL,TRUE,CREATE_NEW_CONSOLE, NULL,zdownloaddir,&si,&term->xyz_Internals->pi))
		{
			//DWORD err = GetLastError();
	                //ErrorMessage("CreateProcess");
	                dbg("Error CreateProcess\n");
			CloseHandle(newstdin);
			CloseHandle(term->xyz_Internals->write_stdin);
			CloseHandle(newstdout);
			CloseHandle(term->xyz_Internals->read_stdout);
			CloseHandle(newstderr);
			CloseHandle(term->xyz_Internals->read_stderr);
			return 1;
		}
	}

	CloseHandle(newstdin);
	CloseHandle(newstdout);
	CloseHandle(newstderr);

	dbg("SPAWN PROCESS COMPLETE\n");
	return 0;
}

int xyz_ReceiveData(Terminal *term, const u_char *buffer, int len)
{
	dbg("xyzReceiveData\n");
	DWORD written;
#if 0
	if (0)
	{
		char *debugbuff;
		char *bb, *p;
		int i;

		debugbuff = _alloca(len*3+128);
		debugbuff[0] = 0;
		bb = debugbuff;
		p = buffer;
		bb += sprintf(bb, "R: %8d   ", time(NULL));
		for(i=0; i < len; i++) {
			bb += sprintf(bb, "%2x ", *p++);
		}
		bb += sprintf(bb, "\n");

		OutputDebugString(debugbuff);
	} else {
		char *debugbuff;
		debugbuff = _alloca(len+128);
		memcpy(debugbuff, buffer, len);
		debugbuff[len] = 0;
		strcat(debugbuff, ">>>>>>>\n");
		OutputDebugString(debugbuff);
	}
#endif
	//dbg("WriteFile\n");
	WriteFile(term->xyz_Internals->write_stdin,buffer,len,&written,NULL);
        char tmp[100];
	//sprintf(tmp,"FileWritten %d\n",len);
	dbg(tmp);

	return 0 ;
}
