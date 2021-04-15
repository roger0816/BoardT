#include "ItemMediaCent.h"

ItemMediaCent::ItemMediaCent(QWidget *parent) : ItemBase(parent)
{

    m_wBg = new QWidget(this);

    m_wBg->setObjectName("m_wBg");

    m_wBg->setStyleSheet("QWidget#m_wBg{background-color:black;}");

    m_wR = new QWidget(m_wBg);

    m_wR->setObjectName("ItemMediaCent_m_wR");

    m_wR->setStyleSheet("QWidget#ItemMediaCent_m_wR{background-color:black;}");

    m_wCent = new QWidget(m_wBg);

    m_wCent->setStyleSheet("background-color:rgb(177,177,177);");

    m_player = new CPlayer(m_wCent);

    m_player->connect(m_player,&CPlayer::playing,this,&ItemMediaCent::playing);

    m_player->setStyleSheet("background-color:rgb(177,177,177);");

    m_title = new QLabel(m_wBg);

    m_title->setStyleSheet("background-color:rgb(255,255,255);");

    m_title->setAlignment(Qt::AlignHCenter);

    m_wFunction = new QWidget(m_wBg);

    m_wFunction->setObjectName("media_function");

    m_wFunction->setStyleSheet("QWidget#media_function{background-color:black};");

    QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
  //  sizePolicy.setHeightForWidth(widget_3->sizePolicy().hasHeightForWidth());

    m_btnPlay = new QPushButton(m_wFunction);

    m_btnPlay->setFocusPolicy(Qt::NoFocus);

    m_btnPlay->setSizePolicy(sizePolicy);

    m_btnPlay->setCheckable(true);

    m_btnPlay->connect(m_btnPlay,&QPushButton::clicked,this,&ItemMediaCent::playAndPause);

    m_btnPlay->setText("Pause");

    m_btnNext = new QPushButton(m_wFunction);

    m_btnNext->setFocusPolicy(Qt::NoFocus);

    m_btnNext->connect(m_btnNext,&QPushButton::clicked,this,&ItemMediaCent::btnNext);


    m_btnNext->setSizePolicy(sizePolicy);


    m_btnNext->setText(">>");

    m_btnPre = new QPushButton(m_wFunction);

    m_btnPre->setFocusPolicy(Qt::NoFocus);

    m_btnPre->connect(m_btnPre,&QPushButton::clicked,this,&ItemMediaCent::btnPre);


    m_btnPre->setSizePolicy(sizePolicy);

    m_btnPre->setText("<<");

    m_btnStop = new QPushButton(m_wFunction);

    m_btnStop->setFocusPolicy(Qt::NoFocus);


    m_btnStop->connect(m_btnStop,&QPushButton::clicked,this,&ItemMediaCent::btnStop);


    m_btnStop->setSizePolicy(sizePolicy);


    m_btnStop->setText("■");

    QHBoxLayout *lay = new QHBoxLayout;

  //  lay->setMargin(50);

    lay->setContentsMargins(80,10,80,10);

    lay->addWidget(m_btnPre);

    lay->addWidget(m_btnPlay);

    lay->addWidget(m_btnStop);

    lay->addWidget(m_btnNext);

    m_wFunction->setLayout(lay);



   // connect(&Global::Instance(),&Global::callPlay,m_player,&CPlayer::setPlayAdnPause);
}

ItemMediaCent::~ItemMediaCent()
{
    m_player->stop();
}

bool ItemMediaCent::init()
{

    getVideo(m_sPath+"/../../../video");

    getConfig();

    //QStringList listSchedult =

  //  QStringList listAction =   m_sPath+"/action.txt";

//    QFileInfoList listDir = QDir(m_sPath).entryInfoList();

//    m_dVideo.clear();

//    foreach(QFileInfo file,list)
//    {
//        if(file.isDir() && file.fileName()!="." && file.fileName()!="..")
//        {
//             m_dVideo.insert(file.filePath(),QStringList());

//        }
//    }



//    QFileInfoList list = QDir(m_sPath).entryInfoList(QStringList()<<"*.mp4");

//    foreach(QFileInfo file ,list)
//        {
//            m_listVideo.append(file.filePath());
//        }


//        if(m_listVideo.length()<1)
//            return false;

//        m_player->openList(m_listVideo);

    m_player->openList(m_dVideo.value(m_listKey.at(0)));

    m_btnPlay->setChecked(true);

    return true;
}

void ItemMediaCent::reSize()
{


    int iT_h = 60;

    int iB_h = 60;

    int iVideoW = (height()-iT_h-iB_h)*1.77777777;

    int iR_w = width()-iVideoW;


    m_wBg->resize(this->size());

    m_title->setGeometry(0,0,width(),iT_h);

    m_wR->setGeometry(this->width()-iR_w,0,iR_w,height());

    m_wFunction->setGeometry(0,height()-iB_h,width()-m_wR->width(),iB_h);


    //m_wR->hide();

    m_wCent->setGeometry(0,iT_h,width()-m_wR->width(),height()-(iT_h+iB_h));

   // m_wCent->resize(640,480);

  //  qDebug()<<"EFG : "<<m_wCent->size();

    m_player->resize(m_wCent->size());
}

void ItemMediaCent::showEvent(QShowEvent *)
{
    reSize();


}

void ItemMediaCent::resizeEvent(QResizeEvent *)
{
    reSize();
}

void ItemMediaCent::getConfig()
{

    QSettings conf(m_sPath+"/conf.ini",QSettings::IniFormat);

    int lbSize = conf.value("Button/txtSize").toInt();

    QFont f;

    f.setPixelSize(lbSize);

    foreach(QPushButton *btn,m_listBtn)
    {
        btn->setFont(f);
    }

    int titleSize = conf.value("Title/txtSize").toInt();

    QFont f2;

    f2.setPixelSize(titleSize);

    m_title->setFont(f);

    m_title->setStyleSheet("color:#"+conf.value("Title/txtColor").toString()
                         +";"+
                           "background-color:#"+conf.value("Title/bgColor").toString()
                                                    +";");






}

void ItemMediaCent::getVideo(QString sPath)
{

    QStringList listDir = QDir(sPath).entryList(QDir::Dirs);



     if(listDir.removeOne("其它"))
         listDir.append("其它");

    int x=0,y=0;


    while(listDir.length()>2 && (x>=0 || y>=0))
    {
          int iTmp = listDir.indexOf(".");
            if(iTmp >=0)
                listDir.removeAt(iTmp);

            x = iTmp;

            iTmp = listDir.indexOf("..");
              if(iTmp >=0)
                  listDir.removeAt(iTmp);

              y = iTmp;
    }

    m_dVideo.clear();


    QVBoxLayout *lay = new QVBoxLayout;

    lay->setContentsMargins(10,40,10,40);

    for(int i=0;i<listDir.length();i++)
    {

        QString sFolder = listDir.at(i) ;

        QStringList list = QDir(sPath+"/"+sFolder).entryList(QStringList()<<"*.mp4");

        qDebug()<<"folder : "<<sFolder<<" , "<<list;

        if(list.length()<1)
            continue;

        QStringList reList;

        for(int j=0;j<list.length();j++)
        {
            reList.append(m_sPath+"/../../../video/"+sFolder+"/"+list.at(j));
        }


        if(list.length()>0)
        {
            m_dVideo.insert(sFolder,reList);
        }

        while(m_listBtn.length()<m_dVideo.keys().length())
        {
            QPushButton *btn = new QPushButton(m_wFunction);

            btn->connect(btn,&QPushButton::clicked,this,&ItemMediaCent::videoClicked);

            btn->hide();

            m_listBtn.append(btn);

        }

        m_listBtn[i]->setText(sFolder);

        lay->addWidget(m_listBtn[i]);

        m_listBtn[i]->show();
    }


    m_wR->setLayout(lay);


    m_listKey = listDir;


}

void ItemMediaCent::playAndPause(bool b)
{

    m_btnPlay->setChecked(b);

    if(m_btnPlay->isChecked())
    {
        m_player->play();

        m_btnPlay->setText("Pause");
    }
    else
    {
        m_player->pause();

        m_btnPlay->setText("Play");
    }
}

void ItemMediaCent::btnPre()
{
    m_player->open(m_sCurrentVideo);

    m_player->play();

    m_btnPlay->setText("Pause");

    m_btnPlay->setChecked(true);
}

void ItemMediaCent::btnNext()
{

    QStringList list =m_dVideo.value(m_listKey[m_iTypeIdx]);

     int iTarget = QTime::currentTime().msec()%list.length();

     m_player->open(list[iTarget]);

     m_player->play();

     m_btnPlay->setText("Pause");

     m_btnPlay->setChecked(true);
}

void ItemMediaCent::btnStop()
{

}

void ItemMediaCent::playing(QString sName)
{
    m_sCurrentVideo = sName;

    m_title->setText(sName.split("/").last().replace(".mp4",""));
}

void ItemMediaCent::videoClicked()
{
      QPushButton *btn =  dynamic_cast<QPushButton*>(sender());

      int iIdx =-1;

      for(int i=0;i<m_listBtn.length();i++)
      {
          if(btn == m_listBtn.at(i))
              iIdx = i ;
      }

      if(iIdx<0 || iIdx>=m_listKey.length())
          return ;

      m_iTypeIdx = iIdx;

      QStringList list =m_dVideo.value(m_listKey[iIdx]);

       int iTarget = QTime::currentTime().msec()%list.length();

       m_player->open(list[iTarget]);

       m_player->play();

       m_btnPlay->setText("Pause");

       m_btnPlay->setChecked(true);


}


