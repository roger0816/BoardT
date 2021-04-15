#include "FuncNfc.h"


#ifdef DEVELOP

#else

FuncNfc::FuncNfc(QObject *parent) : QThread(parent)
{

    PN532_SPI_Init(&pn532);
    //PN532_I2C_Init(&pn532);
    //PN532_UART_Init(&pn532);

    if (PN532_GetFirmwareVersion(&pn532, buff) == PN532_STATUS_OK)
    {
        printf("Found PN532 with firmware version: %d.%d\r\n", buff[1], buff[2]);
        bFindDevice = true;

        PN532_SamConfiguration(&pn532);
    }
    else
    {
        bFindDevice = false;
    }


    //    printf("Waiting for RFID/NFC card...\r\n");

}

void FuncNfc::run()
{
    while (!m_bStop)
    {

        if(!bFindDevice)
            continue;

        uid_len = PN532_ReadPassiveTarget(&pn532, uid, PN532_MIFARE_ISO14443A, 1000);
        if (uid_len == PN532_STATUS_ERROR) {
            //  printf(".");
            fflush(stdout);

            m_sCurrentUid = "";
        }
        else
        {

            QString sUid="";

            for (uint8_t i = 0; i < uid_len; i++)
            {

                QString st = QString("%1").arg(uid[i],2,16,QLatin1Char('0'));


                sUid+=st;
                //printf("%02x ", uid[i]);
            }

            if(sUid!=m_sCurrentUid)
            {
                emit hoverUid(sUid);

              //  qDebug()<<sUid;

            }
            m_sCurrentUid = sUid;



        }

        if(m_sCurrentUid!="")
            m_sPreUid = m_sCurrentUid;



    }
}



#endif
