
#include "eagetmailobj.tlh"
using namespace EAGetMailObjLib;

int _tmain(int argc, _TCHAR* argv[])
{
    const int MailServerPop3 = 0;
    const int MailServerImap4 = 1;
    const int MailServerEWS = 2; 
    const int MailServerDAV = 3; 

    // Initialize COM environment
    ::CoInitialize( NULL );

    // Create a folder named "inbox" under current exe file directory
    // to save the emails retrieved.
    TCHAR szPath[MAX_PATH+1];
    memset( szPath, 0, sizeof(szPath));
    ::GetModuleFileName( NULL, szPath,  MAX_PATH );

    // Change file name to current full path
    LPCTSTR psz = _tcsrchr( szPath, _T('\\'));
    if( psz != NULL )
    {
        szPath[psz-szPath] = _T('\0');
    }
    TCHAR szMailBox[MAX_PATH+1];
    memset( szMailBox, 0, sizeof(szMailBox));
    wsprintf( szMailBox, _T("%s\\inbox"), szPath );
    
    // Create a folder to store emails
    ::CreateDirectory( szMailBox, NULL );
    
    try
    {
        IMailServerPtr oServer = NULL;
        oServer.CreateInstance("EAGetMailObj.MailServer");
        oServer->Server = _T("pop3.emailarchitect.net");
        oServer->User = _T("test@emailarchitect.net");
        oServer->Password = _T("testpassword");
        oServer->Protocol = MailServerPop3;

        // If your POP3 requires SSL connection
        // Please add the following codes
        // oServer->SSLConnection = VARIANT_TRUE;
        // oServer->Port = 995;
    
        IMailClientPtr oClient = NULL;
        oClient.CreateInstance("EAGetMailObj.MailClient");
        oClient->LicenseCode = _T("TryIt");

        oClient->Connect( oServer );
        _tprintf(_T("Connected\r\n"));

        _variant_t infos = oClient->GetMailInfos();
        SAFEARRAY *psa = infos.parray;
        long LBound = 0, UBound = 0;
        SafeArrayGetLBound( psa, 1, &LBound );
        SafeArrayGetUBound( psa, 1, &UBound );
    
        INT count = UBound-LBound+1;
        _tprintf(_T("Total %d emails\r\n"), count );

        for( long i = LBound; i <= UBound; i++ )
        {
            _variant_t vtInfo;
            SafeArrayGetElement( psa, &i, &vtInfo );
            
            IMailInfoPtr pInfo;
            vtInfo.pdispVal->QueryInterface(__uuidof(IMailInfo), (void**)&pInfo);

            TCHAR szFile[MAX_PATH+1];
            memset( szFile, 0, sizeof(szFile));
            
            // Generate a random file name by current local datetime,
            // You can use your method to generate the filename if you do not like it
            SYSTEMTIME curtm;
            ::GetLocalTime( &curtm );
            ::wsprintf( szFile, _T("%s\\%04d%02d%02d%02d%02d%02d%03d%d.eml"),
                szMailBox,
                curtm.wYear,
                curtm.wMonth,
                curtm.wDay,
                curtm.wHour,
                curtm.wMinute,
                curtm.wSecond,
                curtm.wMilliseconds,
                i );

            // Receive email from POP3 server
            IMailPtr oMail = oClient->GetMail(pInfo);

            // Save email to local disk
            oMail->SaveAs( szFile, VARIANT_TRUE );

            // Mark email as deleted from POP3 server.
            oClient->Delete( pInfo );
        }
        
        // Delete method just mark the email as deleted, 
        // Quit method pure the emails from server exactly.
        infos.Clear();
        oClient->Quit();
    }
    catch( _com_error &ep )
    {
        _tprintf( _T("Error: %s"), (const TCHAR*)ep.Description());
    }

    return 0;
}
