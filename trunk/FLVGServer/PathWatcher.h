#ifndef WATCH_H
#define WATCH_H
#define _WIN32_WINNT 0x0500
#include "StdAfx.h"
#include <windows.h>
#include <string>
#include <cassert>

class CMainFrame;
void   SendOutNotify(PFILE_NOTIFY_INFORMATION f_pNotify,CMainFrame* pM);
#define  DeFileWaterBuffer  (1000* (sizeof(FILE_NOTIFY_INFORMATION)+MAX_PATH) )
static CMainFrame* pMainWnd;
enum ACTION { ADDED=1, REMOVED=2, MODIFIED=3, RENAMED=4 };
class FileSystemWatcher
{
public:
    typedef void (__stdcall *LPDEALFUNCTION)( ACTION act, std::string filename1, std::string filename2 );
	
	void SetpMain(CMainFrame* pM)
	{
		pMainWnd = pM;
	}
    bool Run( std::string path, LPDEALFUNCTION dealfun )
    {
        WatchedDir = path;
        DealFun = dealfun;

        DWORD ThreadId;
        //hThread=CreateThread( NULL,0,Routine,this,0,&ThreadId );
        hThread=CreateThread( NULL,0,RoutineTest,this,0,&ThreadId );
        return NULL!=hThread;
    }
    void Close()
    {
        if( NULL != hThread )
        {
            TerminateThread( hThread, 0 );
            hThread = NULL;
        }
        if( INVALID_HANDLE_VALUE != hDir )
        {
            CloseHandle( hDir );
            hDir = INVALID_HANDLE_VALUE;
        }
    }
    FileSystemWatcher() : DealFun(NULL), hThread(NULL), hDir(INVALID_HANDLE_VALUE)
    {
    }
    ~FileSystemWatcher()
    {
        Close();
    }

private:
    std::string WatchedDir;
    LPDEALFUNCTION DealFun;
    HANDLE hThread;
    HANDLE hDir;
private:
    FileSystemWatcher( const FileSystemWatcher& );
    FileSystemWatcher operator=( const FileSystemWatcher );
private:
    static DWORD WINAPI Routine( LPVOID lParam )
    {
        FileSystemWatcher* obj = (FileSystemWatcher*)lParam;

       /*
        obj->hDir = CreateFile(
            obj->WatchedDir.c_str(),
            GENERIC_READ|GENERIC_WRITE,
            FILE_SHARE_READ|FILE_SHARE_WRITE|FILE_SHARE_DELETE,
            NULL,
            OPEN_EXISTING,
            FILE_FLAG_BACKUP_SEMANTICS,
            NULL
        );
        */
        //hcs change 
        obj->hDir = CreateFile(
         obj->WatchedDir.c_str(),                           // pointer to the file name
         FILE_LIST_DIRECTORY,                // access (read/write) mode
         FILE_SHARE_READ|FILE_SHARE_DELETE,  // share mode
         NULL,                               // security descriptor
         OPEN_EXISTING,                      // how to create
         FILE_FLAG_BACKUP_SEMANTICS,         // file attributes
         NULL                                // file with attributes to copy
                                );
        if( INVALID_HANDLE_VALUE == obj->hDir ) return false;

        char buf[ 50*(sizeof(FILE_NOTIFY_INFORMATION)+MAX_PATH) ];
        FILE_NOTIFY_INFORMATION* pNotify=(FILE_NOTIFY_INFORMATION *)buf;
        DWORD BytesReturned;
        while(true)
        {
            memset(buf,0,sizeof(buf));
            if( ReadDirectoryChangesW( obj->hDir,
                pNotify,
                sizeof(buf),
                true,
                FILE_NOTIFY_CHANGE_FILE_NAME|
                FILE_NOTIFY_CHANGE_DIR_NAME|
                FILE_NOTIFY_CHANGE_ATTRIBUTES|
                FILE_NOTIFY_CHANGE_SIZE|
                FILE_NOTIFY_CHANGE_LAST_WRITE|
                FILE_NOTIFY_CHANGE_LAST_ACCESS|
                FILE_NOTIFY_CHANGE_CREATION|
                FILE_NOTIFY_CHANGE_SECURITY,
                &BytesReturned,
                NULL,
                NULL ) )
            {
                
                char tmp[MAX_PATH], str1[MAX_PATH], str2[MAX_PATH];

                memset( tmp, 0, sizeof(tmp) );
                WideCharToMultiByte( CP_ACP,0,pNotify->FileName,pNotify->FileNameLength/2,tmp,99,NULL,NULL );
                strcpy( str1, tmp );

                if( 0 != pNotify->NextEntryOffset )
                {
                    PFILE_NOTIFY_INFORMATION p = (PFILE_NOTIFY_INFORMATION)((char*)pNotify+pNotify->NextEntryOffset);
                    memset( tmp, 0, sizeof(tmp) );
                    WideCharToMultiByte( CP_ACP,0,p->FileName,p->FileNameLength/2,tmp,99,NULL,NULL );
                    strcpy( str2, tmp );
                }


                //obj->DealFun( (ACTION)pNotify->Action, str1, str2 );
                
                SendOutNotify(pNotify,pMainWnd);

            }
            else
            {
                break;
            }
        }

        return 0;
    }

    static DWORD WINAPI RoutineTest( LPVOID lParam )
    {
        FileSystemWatcher* obj = (FileSystemWatcher*)lParam;

        //hcs change 
        obj->hDir = CreateFile(
         obj->WatchedDir.c_str(),            // pointer to the file name
         FILE_LIST_DIRECTORY,                // access (read/write) mode
         FILE_SHARE_READ|FILE_SHARE_DELETE,  // share mode
         NULL,                               // security descriptor
         OPEN_EXISTING,                      // how to create
         FILE_FLAG_BACKUP_SEMANTICS,         // file attributes
         NULL                                // file with attributes to copy
                                );
        if( INVALID_HANDLE_VALUE == obj->hDir ) return false;

        char *pcBufferNs=new char[DeFileWaterBuffer];
        FILE_NOTIFY_INFORMATION* pNotify=(FILE_NOTIFY_INFORMATION *)pcBufferNs;
        DWORD BytesReturned;
        while(true)
        {
            memset(pcBufferNs,0,DeFileWaterBuffer);
            BytesReturned=0;
            if( 
               ReadDirectoryChangesW( 
                obj->hDir,
                pNotify,
                DeFileWaterBuffer,
                true,
                FILE_NOTIFY_CHANGE_FILE_NAME|
                FILE_NOTIFY_CHANGE_DIR_NAME|
                FILE_NOTIFY_CHANGE_ATTRIBUTES|
                FILE_NOTIFY_CHANGE_SIZE|
                FILE_NOTIFY_CHANGE_LAST_WRITE|
                FILE_NOTIFY_CHANGE_LAST_ACCESS|
                FILE_NOTIFY_CHANGE_CREATION|
                FILE_NOTIFY_CHANGE_SECURITY,
                &BytesReturned,
                NULL,
                NULL ) )
            {
                /*
                char tmp[MAX_PATH], str1[MAX_PATH], str2[MAX_PATH];

                memset( tmp, 0, sizeof(tmp) );
                WideCharToMultiByte( CP_ACP,0,pNotify->FileName,pNotify->FileNameLength/2,tmp,99,NULL,NULL );
                strcpy( str1, tmp );

                if( 0 != pNotify->NextEntryOffset )
                {
                    PFILE_NOTIFY_INFORMATION p = (PFILE_NOTIFY_INFORMATION)((char*)pNotify+pNotify->NextEntryOffset);
                    memset( tmp, 0, sizeof(tmp) );
                    WideCharToMultiByte( CP_ACP,0,p->FileName,p->FileNameLength/2,tmp,99,NULL,NULL );
                    strcpy( str2, tmp );
                }


                obj->DealFun( (ACTION)pNotify->Action, str1, str2 );
                */
                if(BytesReturned> 0)
                {
                  SendOutNotify(pNotify,pMainWnd);
                }
                else
                {
                  //AfxMessageBox("Buffer is small");
                  MessageBox(0,"Buffer is small","error",MB_OK);
                }
            }
            else
            {
                break;
            }
        }
        delete [] pcBufferNs;
        return 0;
    }

};
#endif