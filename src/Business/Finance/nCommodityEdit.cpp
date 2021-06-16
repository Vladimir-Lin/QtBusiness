#include <business.h>

N::CommodityEdit:: CommodityEdit  ( QWidget * parent , Plan * p )
                 : TreeDock       (           parent ,        p )
                 , Ownership      ( 0                           ,
                                    Types::Organization         ,
                                    Groups::Subordination       )
                 , FinanceManager (                           p )
                 , GroupItems     (                           p )
                 , dropAction     ( false                       )
                 , Sorting        ( Qt::AscendingOrder          )
{
  Configure ( ) ;
}

N::CommodityEdit::~CommodityEdit(void)
{
}

QMimeData * N::CommodityEdit::dragMime (void)
{
  QMimeData * mime = standardMime("commodity") ;
  nKickOut ( IsNull(mime) , NULL )             ;
  return mime                                  ;
}

bool N::CommodityEdit::hasItem(void)
{
  UUIDs Uuids = selectedUuids(0) ;
  return ( Uuids.count() > 0 )   ;
}

bool N::CommodityEdit::startDrag(QMouseEvent * event)
{
  QTreeWidgetItem * atItem = itemAt(event->pos())           ;
  nKickOut ( IsNull(atItem) , false )                       ;
  nKickOut (!IsMask(event->buttons(),Qt::LeftButton),false) ;
  dragPoint = event->pos()                                  ;
  nKickOut (!atItem->isSelected(),false)                    ;
  nKickOut (!PassDragDrop,true)                             ;
  return true                                               ;
}

bool N::CommodityEdit::fetchDrag(QMouseEvent * event)
{
  nKickOut ( !IsMask(event->buttons(),Qt::LeftButton) , false) ;
  QPoint pos = event->pos()                                    ;
  pos -= dragPoint                                             ;
  return ( pos.manhattanLength() > qApp->startDragDistance() ) ;
}

void N::CommodityEdit::dragDone(Qt::DropAction dropIt,QMimeData * mime)
{
}

bool N::CommodityEdit::finishDrag(QMouseEvent * event)
{
  return true ;
}

bool N::CommodityEdit::acceptDrop(QWidget * source,const QMimeData * mime)
{
  nKickOut           ( nEqual(source,this) , false ) ;
  return dropHandler ( mime                        ) ;
}

bool N::CommodityEdit::dropNew(QWidget * source,const QMimeData * mime,QPoint pos)
{
  Alert ( Action ) ;
  return true      ;
}

void N::CommodityEdit::Configure(void)
{
  LimitValues [ 0 ] =  0                              ;
  LimitValues [ 1 ] = 48                              ;
  LimitValues [ 2 ] =  0                              ;
  PassDragDrop      = false                           ;
  /////////////////////////////////////////////////////
  SetupMessages           (                         ) ;
  SetupIcons              (                         ) ;
  setWindowIcon           ( LocalIcons [ "Title" ]  ) ;
  /////////////////////////////////////////////////////
  NewTreeWidgetItem       ( head                    ) ;
  setWindowTitle          (     tr("Commodities")   ) ;
  head->setText           ( 0 , tr("Product"    )   ) ;
  head->setText           ( 1 , tr("Identifier" )   ) ;
  head->setText           ( 2 , ""                  ) ;
  /////////////////////////////////////////////////////
  setAccessibleName       ( "N::CommodityEdit"      ) ;
  setObjectName           ( "N::CommodityEdit"      ) ;
  setFocusPolicy          ( Qt::WheelFocus          ) ;
  setDragDropMode         ( DragDrop                ) ;
  setAlternatingRowColors ( true                    ) ;
  setRootIsDecorated      ( false                   ) ;
  setSelectionMode        ( ExtendedSelection       ) ;
  setColumnCount          ( 3                       ) ;
  setAllAlignments        ( head,Qt::AlignCenter    ) ;
  setFont                 ( head,Fonts::ListView    ) ;
  setHeaderItem           ( head                    ) ;
  setColumnWidth          ( 2 , 3                   ) ;
  MountClicked            ( 2                       ) ;
  /////////////////////////////////////////////////////
  setDropFlag             ( DropFont         , true ) ;
  setDropFlag             ( DropPen          , true ) ;
  setDropFlag             ( DropBrush        , true ) ;
  setDropFlag             ( DropText         , true ) ;
  setDropFlag             ( DropAlbum        , true ) ;
  setDropFlag             ( DropDocument     , true ) ;
  setDropFlag             ( DropOrganization , true ) ;
  setDropFlag             ( DropPeople       , true ) ;
  setDropFlag             ( DropPicture      , true ) ;
  /////////////////////////////////////////////////////
  plan -> setFont         ( this                    ) ;
  PassDragDrop = false                                ;
}

void N::CommodityEdit::SetupMessages(void)
{
  LocalMsgs [ CommodityMsgPage       ] = tr("Total %1 organizations"   ) ;
  LocalMsgs [ CommodityMsgProduct    ] = tr("Product"                  ) ;
  LocalMsgs [ CommodityMsgSearch     ] = tr("Search product name"      ) ;
  LocalMsgs [ CommodityMsgIdentifier ] = tr("Identifier"               ) ;
  LocalMsgs [ CommodityMsgSearchId   ] = tr("Search product identifier") ;
  LocalMsgs [ CommodityMsgExport     ] = tr("Export commodities"       ) ;
  LocalMsgs [ CommodityMsgAllFiles   ] = tr("All files (*.*)"          ) ;
  LocalMsgs [ CommodityMsgPlainText  ] = tr("Plain text (*.txt)"       ) ;
}

void N::CommodityEdit::SetupIcons(void)
{
  LocalIcons [ "Title"  ] = QIcon ( ":/images/oneself.png" ) ;
  LocalIcons [ "Update" ] = QIcon ( ":/images/update.png"  ) ;
  LocalIcons [ "New"    ] = QIcon ( ":/images/new.png"     ) ;
  LocalIcons [ "Save"   ] = QIcon ( ":/images/save.png"    ) ;
}

bool N::CommodityEdit::FocusIn(void)
{
  nKickOut          ( IsNull(plan) , true                ) ;
  DisableAllActions (                                    ) ;
  AssignAction      ( Label        , windowTitle     ( ) ) ;
  LinkAction        ( Refresh      , startup         ( ) ) ;
  LinkAction        ( Insert       , New             ( ) ) ;
  LinkAction        ( Paste        , Paste           ( ) ) ;
  LinkAction        ( Export       , Export          ( ) ) ;
  LinkAction        ( Copy         , CopyToClipboard ( ) ) ;
  LinkAction        ( SelectNone   , SelectNone      ( ) ) ;
  LinkAction        ( SelectAll    , SelectAll       ( ) ) ;
  LinkAction        ( Font         , setFont         ( ) ) ;
  LinkAction        ( Language     , Language        ( ) ) ;
  LinkAction        ( PreviousPage , PageUp          ( ) ) ;
  LinkAction        ( NextPage     , PageDown        ( ) ) ;
  LinkAction        ( GoHome       , PageHome        ( ) ) ;
  LinkAction        ( GoEnd        , PageEnd         ( ) ) ;
  return true                                              ;
}

void  N::CommodityEdit::run(int T,ThreadData * d)
{
  nDropOut         ( ! IsContinue ( d ) ) ;
  switch           ( T                  ) {
    case 10001                            :
      startLoading (                    ) ;
      List         ( d                  ) ;
      stopLoading  (                    ) ;
    break                                 ;
    case 10002                            :
      startLoading (                    ) ;
      Paste        ( d                  ) ;
      stopLoading  (                    ) ;
    break                                 ;
    case 10003                            :
      startLoading (                    ) ;
      GroupJoin    ( d                  ) ;
      stopLoading  (                    ) ;
    break                                 ;
  }                                       ;
}

UUIDs N::CommodityEdit::LoadUuids(SqlConnection & SC)
{
  UUIDs Uuids                                           ;
  if ( isStandby ( ) )                                  {
    Uuids = SC . Uuids                                  (
      PlanTable(Commodities)                            ,
      "uuid"                                            ,
      SC . OrderBy ( "id" , (Qt::SortOrder) Sorting ) ) ;
  } else                                                {
    /////////////////////////////////////////////////////
    GroupItems GI ( plan )                              ;
    GI . AutoMap    = true                              ;
    GI . GroupTable = GI . LookTable                    (
                        ObjectType ( )                  ,
                        Types::Commodity                ,
                        Connexion  ( )                ) ;
    Uuids = GI . Subordination                          (
      SC                                                ,
      ObjectUuid ( )                                    ,
      ObjectType ( )                                    ,
      Types::Commodity                                  ,
      Connexion  ( )                                    ,
      SC . OrderBy ( "id" , (Qt::SortOrder) Sorting ) ) ;
  }                                                     ;
  ///////////////////////////////////////////////////////
  LimitValues [ 2 ] = Uuids . count ( )                 ;
  if ( LimitValues[0] >= 0 && LimitValues[1] > 0 )      {
    UUIDs UX                                            ;
    int   sid = LimitValues [ 0 ]                       ;
    int   tid = LimitValues [ 1 ]                       ;
    int   eid = LimitValues [ 2 ]                       ;
    if ( ( sid + tid ) < eid ) eid = sid + tid          ;
    for (int i=sid;i<eid;i++) UX << Uuids [ i ]         ;
    Uuids = UX                                          ;
  }                                                     ;
  ///////////////////////////////////////////////////////
  return Uuids                                          ;
}

void N::CommodityEdit::LoadNames(SqlConnection & SC,UUIDs & U)
{
  SUID u = 0                                            ;
  foreach ( u , U )                                     {
    QStringList Names = GroupItems::Names    ( SC , u ) ;
    if ( Names . count ( ) > 0 )                        {
      QTreeWidgetItem * it                              ;
      QString           name                            ;
      it   = addItem ( Names . first ( ) , u , 0      ) ;
      name = FinanceManager::FetchIdentifier ( SC , u ) ;
      it  -> setText ( 1 , name                       ) ;
    }                                                   ;
  }                                                     ;
}

SUID N::CommodityEdit::AppendUuid(SqlConnection & SC)
{
  return FinanceManager::appendCommodity ( SC ) ;
}

bool N::CommodityEdit::AppendName(SqlConnection & SC,SUID u,QString name)
{
  SUID nuid = FinanceManager::appendNamemap (
                SC                          ,
                u                           ,
                vLanguageId                 ,
                name                      ) ;
  return ( nuid > 0 )                       ;
}

void N::CommodityEdit::setProduct(SqlConnection & SC,SUID u,QString name)
{
  FinanceManager::assureIdentifier ( SC , u , name ) ;
}

bool N::CommodityEdit::dropText(QWidget * source,QPointF pos,const QString & text)
{
  dropAction = true  ;
  Paste ( text )     ;
  dropAction = false ;
  return true        ;
}

bool N::CommodityEdit::dropAlbums(QWidget * source,QPointF psf,const UUIDs & Uuids)
{
  if ( source == this ) return false      ;
  /////////////////////////////////////////
  QPoint pos = psf . toPoint ( )          ;
  QTreeWidgetItem * item = itemAt ( pos ) ;
  if (IsNull(item))                       {
    Alert ( Error )                       ;
    return false                          ;
  }                                       ;
  /////////////////////////////////////////
  VarArgs args                            ;
  dropAction = true                       ;
  /////////////////////////////////////////
  args << nTreeUuid ( item  , 0    )      ;
  args << Types::Commodity                ;
  args << Types::Album                    ;
  toVariants        ( Uuids , args )      ;
  start             ( 10003 , args )      ;
  /////////////////////////////////////////
  dropAction = false                      ;
  /////////////////////////////////////////
  return true                             ;
}

bool N::CommodityEdit::dropDocuments(QWidget * source,QPointF psf,const UUIDs & Uuids)
{
  if ( source == this ) return false      ;
  /////////////////////////////////////////
  QPoint pos = psf . toPoint ( )          ;
  QTreeWidgetItem * item = itemAt ( pos ) ;
  if (IsNull(item))                       {
    Alert ( Error )                       ;
    return false                          ;
  }                                       ;
  /////////////////////////////////////////
  VarArgs args                            ;
  dropAction = true                       ;
  /////////////////////////////////////////
  args << nTreeUuid ( item  , 0    )      ;
  args << Types::Commodity                ;
  args << Types::Document                 ;
  toVariants        ( Uuids , args )      ;
  start             ( 10003 , args )      ;
  /////////////////////////////////////////
  dropAction = false                      ;
  /////////////////////////////////////////
  return true                             ;
}

bool N::CommodityEdit::dropOrganizations(QWidget * source,QPointF psf,const UUIDs & Uuids)
{
  if ( source == this ) return false      ;
  /////////////////////////////////////////
  QPoint pos = psf . toPoint ( )          ;
  QTreeWidgetItem * item = itemAt ( pos ) ;
  if (IsNull(item))                       {
    Alert ( Error )                       ;
    return false                          ;
  }                                       ;
  /////////////////////////////////////////
  VarArgs args                            ;
  dropAction = true                       ;
  /////////////////////////////////////////
  args << nTreeUuid ( item  , 0    )      ;
  args << Types::Organization             ;
  args << Types::Commodity                ;
  toVariants        ( Uuids , args )      ;
  start             ( 10003 , args )      ;
  /////////////////////////////////////////
  dropAction = false                      ;
  /////////////////////////////////////////
  return true                             ;
}

bool N::CommodityEdit::dropPeople(QWidget * source,QPointF psf,const UUIDs & Uuids)
{
  if ( source == this ) return false      ;
  /////////////////////////////////////////
  QPoint pos = psf . toPoint ( )          ;
  QTreeWidgetItem * item = itemAt ( pos ) ;
  if (IsNull(item))                       {
    Alert ( Error )                       ;
    return false                          ;
  }                                       ;
  /////////////////////////////////////////
  VarArgs args                            ;
  dropAction = true                       ;
  /////////////////////////////////////////
  args << nTreeUuid ( item  , 0    )      ;
  args << Types::Commodity                ;
  args << Types::People                   ;
  toVariants        ( Uuids , args )      ;
  start             ( 10003 , args )      ;
  /////////////////////////////////////////
  dropAction = false                      ;
  /////////////////////////////////////////
  return true                             ;
}

bool N::CommodityEdit::dropPictures(QWidget * source,QPointF psf,const UUIDs & Uuids)
{
  if ( source == this ) return false      ;
  /////////////////////////////////////////
  QPoint pos = psf . toPoint ( )          ;
  QTreeWidgetItem * item = itemAt ( pos ) ;
  if (IsNull(item))                       {
    Alert ( Error )                       ;
    return false                          ;
  }                                       ;
  /////////////////////////////////////////
  VarArgs args                            ;
  dropAction = true                       ;
  /////////////////////////////////////////
  args << nTreeUuid ( item  , 0    )      ;
  args << Types::Commodity                ;
  args << Types::Picture                  ;
  toVariants        ( Uuids , args )      ;
  start             ( 10003 , args )      ;
  /////////////////////////////////////////
  dropAction = false                      ;
  /////////////////////////////////////////
  return true                             ;
}

void N::CommodityEdit::GroupJoin(ThreadData * d)
{
  nDropOut ( ! IsContinue ( d ) )                         ;
  if ( d -> Arguments . count ( ) < 4 ) return            ;
  SUID  u  = d -> Arguments [ 0 ] . toULongLong ( )       ;
  int   t1 = d -> Arguments [ 1 ] . toInt       ( )       ;
  int   t2 = d -> Arguments [ 2 ] . toInt       ( )       ;
  UUIDs U                                                 ;
  /////////////////////////////////////////////////////////
  for (int i = 3 ; i < d -> Arguments . count ( ) ; i++ ) {
    U << d -> Arguments [ i ] . toULongLong ( )           ;
  }                                                       ;
  /////////////////////////////////////////////////////////
  EnterSQL        ( SC , plan -> sql )                    ;
    GroupItems GI ( plan             )                    ;
    GI . AutoMap    = true                                ;
    GI . GroupTable = GI . LookTable                      (
                        t1                                ,
                        t2                                ,
                        Groups::Subordination           ) ;
    GI . Join                                             (
      SC                                                  ,
      u                                                   ,
      t1                                                  ,
      t2                                                  ,
      Groups::Subordination                               ,
      0                                                   ,
      U                                                 ) ;
  LeaveSQL        ( SC , plan -> sql )                    ;
  /////////////////////////////////////////////////////////
  Alert           ( Done             )                    ;
}

bool N::CommodityEdit::List(ThreadData * d)
{ Q_UNUSED    ( d ) ;
  return List (   ) ;
}

bool N::CommodityEdit::List(void)
{
  emit clearItems  (                  ) ;
  emit setEnabling ( false            ) ;
  EnterSQL         ( SC , plan -> sql ) ;
    UUIDs U                             ;
    U = LoadUuids  ( SC               ) ;
    LoadNames      ( SC , U           ) ;
  LeaveSQL         ( SC , plan -> sql ) ;
  emit setEnabling ( true             ) ;
  emit AutoFit     (                  ) ;
  reportItems      (                  ) ;
  Alert            ( Done             ) ;
  return true                           ;
}

bool N::CommodityEdit::startup(void)
{
  start ( 10001 ) ;
  return true     ;
}

void N::CommodityEdit::doubleClicked(QTreeWidgetItem * item,int column)
{
  nDropOut         ( column > 1            ) ;
  QLineEdit * line                           ;
  removeOldItem    (                       ) ;
  line  = setLineEdit                        (
            item                             ,
            column                           ,
            SIGNAL ( editingFinished ( ) )   ,
            SLOT   ( editingFinished ( ) ) ) ;
  line -> setFocus ( Qt::TabFocusReason    ) ;
}

void N::CommodityEdit::New(void)
{
  NewTreeWidgetItem ( IT                    ) ;
  IT -> setData     ( 0  , Qt::UserRole , 0 ) ;
  setAlignments     ( IT                    ) ;
  addTopLevelItem   ( IT                    ) ;
  scrollToItem      ( IT                    ) ;
  doubleClicked     ( IT , 0                ) ;
}

void N::CommodityEdit::editingFinished(void)
{
  nDropOut                   ( IsNull ( ItemEditing ) ) ;
  QLineEdit * line = Casting ( QLineEdit , ItemWidget ) ;
  if (IsNull(line)) return                              ;
  ItemEditing -> setText ( ItemColumn , line->text()  ) ;
  ///////////////////////////////////////////////////////
  SUID    uuid   = nTreeUuid(ItemEditing,0)             ;
  QString name   = line->text()                         ;
  int     column = ItemColumn                           ;
  EnterSQL ( SC , plan->sql )                           ;
    switch (column)                                     {
      case 0                                            :
        if (uuid<=0 && name.length()>0)                 {
          uuid = AppendUuid(SC)                         ;
          ItemEditing->setData(0,Qt::UserRole,uuid)     ;
        }                                               ;
        if (uuid>0 && name.length()>0)                  {
          AppendName(SC,uuid,name)                      ;
        }                                               ;
        removeOldItem()                                 ;
      break                                             ;
      case 1                                            :
        setProduct    ( SC , uuid , name )              ;
        removeOldItem (                  )              ;
      break                                             ;
    }                                                   ;
  LeaveSQL ( SC , plan->sql )                           ;
  Alert    ( Done           )                           ;
}

void N::CommodityEdit::Paste(ThreadData * d)
{
  nDropOut ( ! IsContinue ( d ) )                     ;
  if ( d -> Arguments . count ( ) < 1 ) return        ;
  QString text = d -> Arguments [ 0 ] . toString ( )  ;
  nDropOut ( text . length ( ) <= 0 )                 ;
  QStringList sl = text . split ( "\n" )              ;
  EnterSQL ( SC , plan -> sql )                       ;
    for (int i = 0 ; i < sl . count ( ) ; i++ )       {
      QString s = sl[i]                               ;
      s = s . replace ( "\r" , "" )                   ;
      s = s . replace ( "\n" , "" )                   ;
      if ( s . length ( ) > 0 )                       {
        SUID u = AppendUuid ( SC )                    ;
        if ( ( u > 0 ) && AppendName ( SC , u , s ) ) {
          addItem ( s , u , 0 )                       ;
        }                                             ;
      }                                               ;
    }                                                 ;
  LeaveSQL ( SC , plan -> sql )                       ;
  Alert    ( Done             )                       ;
}

void N::CommodityEdit::Paste(QString text)
{
  nDropOut ( text . length ( ) <= 0 ) ;
  VarArgs args                        ;
  args << text                        ;
  start    ( 10002 , args           ) ;
}

void N::CommodityEdit::Paste(void)
{
  Paste ( nClipboardText ) ;
}

void N::CommodityEdit::Export(void)
{
  QString filename = plan -> Temporary ( "" )                       ;
  QString filters                                                   ;
  filters  = LocalMsgs [ CommodityMsgAllFiles  ]                    ;
  filters += ";;\n"                                                 ;
  filters += LocalMsgs [ CommodityMsgPlainText ]                    ;
  if ( plan -> Variables . contains ( "CommodityEdit" ) )           {
    filename = plan -> Variables [ "CommodityEdit" ] . toString ( ) ;
  }                                                                 ;
  filename = QFileDialog::getSaveFileName                           (
                       this                                         ,
                       LocalMsgs [ CommodityMsgExport ]             ,
                       filename                                     ,
                       filters                                    ) ;
  nDropOut ( filename.length() <= 0 )                               ;
  QFileInfo FXI ( filename )                                        ;
  QString   path = FXI . absoluteDir ( ) . absolutePath ( )         ;
  plan -> Variables [ "CommodityEdit" ] = path                      ;
  ///////////////////////////////////////////////////////////////////
  QStringList L                                                     ;
  QString     S                                                     ;
  QByteArray  B                                                     ;
  ///////////////////////////////////////////////////////////////////
  for (int i = 0 ; i < topLevelItemCount ( ) ; i++ )                {
    QTreeWidgetItem * it = topLevelItem ( i )                       ;
    QString n = it -> text ( 0 )                                    ;
    if ( ! isColumnHidden ( 1 ) )                                   {
      n += "    "                                                   ;
      n += it -> text ( 1 )                                         ;
    }                                                               ;
    L << n                                                          ;
  }                                                                 ;
  ///////////////////////////////////////////////////////////////////
  if             ( L . count ( ) <= 0 ) return                      ;
  S = L . join   ( "\r\n"             )                             ;
  B = S . toUtf8 (                    )                             ;
  File::toFile   ( filename , B       )                             ;
}

void N::CommodityEdit::Copy(void)
{
  QStringList s                           ;
  for (int i=0;i<topLevelItemCount();i++) {
    if (topLevelItem(i)->isSelected())    {
      s << topLevelItem(i)->text(0)       ;
    }                                     ;
  }                                       ;
  nDropOut      ( s . count ( ) <= 0 )    ;
  nSetClipboard ( s . join  ( "\r\n" ) )  ;
}

void N::CommodityEdit::SearchIdentifier(void)
{
  QTreeWidgetItem *  item  = currentItem()             ;
  int                index = 0                         ;
  QString            name  = ""                        ;
  bool               okay  = false                     ;
  if (NotNull(item)) index = indexOfTopLevelItem(item) ;
  name = QInputDialog::getText                         (
           this                                        ,
           LocalMsgs [ CommodityMsgSearchId   ]        ,
           LocalMsgs [ CommodityMsgIdentifier ]        ,
           QLineEdit::Normal                           ,
           ""                                          ,
           &okay                                     ) ;
  nDropOut ( !okay              )                      ;
  nDropOut ( name.length() <= 0 )                      ;
  okay = false                                         ;
  for (int i=index;!okay && i<topLevelItemCount();i++) {
    item = topLevelItem(i)                             ;
    if (item->text(1).contains(name))                  {
      scrollToItem        ( item )                     ;
      item -> setSelected ( true )                     ;
      okay = true                                      ;
    }                                                  ;
  }                                                    ;
  if (okay) Alert ( Done  )                            ;
       else Alert ( Error )                            ;
}

void N::CommodityEdit::SearchProduct(void)
{
  QTreeWidgetItem *  item  = currentItem()             ;
  int                index = 0                         ;
  QString            name  = ""                        ;
  bool               okay  = false                     ;
  if (NotNull(item)) index = indexOfTopLevelItem(item) ;
  name = QInputDialog::getText                         (
           this                                        ,
           LocalMsgs [ CommodityMsgSearch  ]           ,
           LocalMsgs [ CommodityMsgProduct ]           ,
           QLineEdit::Normal                           ,
           ""                                          ,
           &okay                                     ) ;
  nDropOut ( !okay              )                      ;
  nDropOut ( name.length() <= 0 )                      ;
  okay = false                                         ;
  for (int i=index;!okay && i<topLevelItemCount();i++) {
    item = topLevelItem(i)                             ;
    if (item->text(0).contains(name))                  {
      scrollToItem        ( item )                     ;
      item -> setSelected ( true )                     ;
      okay = true                                      ;
    }                                                  ;
  }                                                    ;
  if (okay) Alert ( Done  )                            ;
       else Alert ( Error )                            ;
}

bool N::CommodityEdit::Menu(QPoint pos)
{
  QTreeWidgetItem * item = itemAt  ( pos )                              ;
  MenuManager       mm (this)                                           ;
  QMenu           * ml                                                  ;
  QMenu           * me                                                  ;
  QMenu           * ms                                                  ;
  QAction         * aa                                                  ;
  QMenu           * mp       = NULL                                     ;
  int               StartId  = 0                                        ;
  int               PageSize = 0                                        ;
  QString           name     = ""                                       ;
  SUID              u        = 0                                        ;
  ///////////////////////////////////////////////////////////////////////
  if ( NotNull ( item ) )                                               {
    name = item -> text (        0 )                                    ;
    u    = nTreeUuid    ( item , 0 )                                    ;
  }                                                                     ;
  ///////////////////////////////////////////////////////////////////////
  if ( LimitValues [ 2 ] > 0 )                                          {
    mp = PageMenu ( mm                                                  ,
                    LocalMsgs [ CommodityMsgPage ]                      ,
                    StartId                                             ,
                    PageSize                                          ) ;
  }                                                                     ;
  ///////////////////////////////////////////////////////////////////////
  me = mm . addMenu   (            tr("Edit"                        ) ) ;
  mm . add            ( me                                              ,
                        101                                             ,
                        LocalIcons [ "Update" ]                         ,
                        tr("Refresh"                                ) ) ;
  mm . addSeparator   ( me                                            ) ;
  mm . add            ( me , 504 , tr("Copy selections to clipboard") ) ;
  mm . add            ( me , 501 , tr("Select all"                  ) ) ;
  mm . add            ( me , 502 , tr("Select none"                 ) ) ;
  mm . add            ( me , 503 , tr("Set font"                    ) ) ;
  ///////////////////////////////////////////////////////////////////////
  if (NotNull(item))                                                    {
    ml = mm . addMenu (            tr("Contents"                    ) ) ;
    mm . add          ( ml , 901 , tr("Manifest"                    ) ) ;
    mm . add          ( ml , 902 , tr("Product owners"              ) ) ;
    mm . add          ( ml , 903 , tr("Documents"                   ) ) ;
    mm . add          ( ml , 904 , tr("Name lists"                  ) ) ;
    mm . add          ( ml , 905 , tr("Gallery"                     ) ) ;
    mm . add          ( ml , 906 , tr("People"                      ) ) ;
  }                                                                     ;
  ///////////////////////////////////////////////////////////////////////
  ms = mm . addMenu   (            tr("Search"                      ) ) ;
  mm . add            ( ms , 801 , tr("Product"                     ) ) ;
  mm . add            ( ms , 802 , tr("Identifier"                  ) ) ;
  ///////////////////////////////////////////////////////////////////////
  mm . addSeparator   (                                               ) ;
  mm . add            ( 201                                             ,
                        LocalIcons [ "New" ]                            ,
                        tr("New product"                            ) ) ;
  mm . add            ( 301                                             ,
                        LocalIcons [ "Save" ]                           ,
                        tr("Save commodities as ..."                ) ) ;
  mm . addSeparator   (                                               ) ;
  DockingMenu         ( mm                                            ) ;
  ///////////////////////////////////////////////////////////////////////
  mm . setFont        ( plan                                          ) ;
  aa = mm . exec      (                                               ) ;
  ///////////////////////////////////////////////////////////////////////
  if                  ( IsNull ( aa )                                 ) {
    PageChanged       ( StartId , PageSize                            ) ;
    return true                                                         ;
  }                                                                     ;
  ///////////////////////////////////////////////////////////////////////
  if ( RunDocking ( mm , aa ) ) return true                             ;
  ///////////////////////////////////////////////////////////////////////
  switch               ( mm [ aa ] )                                    {
    case 101                                                            :
      List             (           )                                    ;
    break                                                               ;
    case 201                                                            :
      New              (           )                                    ;
    break                                                               ;
    case 301                                                            :
      Export           (           )                                    ;
    break                                                               ;
    case 501                                                            :
      SelectAll        (           )                                    ;
    break                                                               ;
    case 502                                                            :
      SelectNone       (           )                                    ;
    break                                                               ;
    case 503                                                            :
      setFont          (           )                                    ;
    break                                                               ;
    case 504                                                            :
      Copy             (           )                                    ;
    break                                                               ;
    case 801                                                            :
      SearchProduct    (           )                                    ;
    break                                                               ;
    case 802                                                            :
      SearchIdentifier (           )                                    ;
    break                                                               ;
    case 901                                                            :
      emit Manifest    ( name , u  )                                    ;
    break                                                               ;
    case 902                                                            :
      emit Owners      ( name , u  )                                    ;
    break                                                               ;
    case 903                                                            :
      emit Documents   ( name , u  )                                    ;
    break                                                               ;
    case 904                                                            :
      emit EditNames   ( name , u  )                                    ;
    break                                                               ;
    case 905                                                            :
      emit Gallery     ( name , u  )                                    ;
    break                                                               ;
    case 906                                                            :
      emit People      ( name , u  )                                    ;
    break                                                               ;
  }                                                                     ;
  ///////////////////////////////////////////////////////////////////////
  if            ( NotNull ( mp )               )                        {
    RunPageMenu ( mm , aa , StartId , PageSize )                        ;
    PageChanged (           StartId , PageSize )                        ;
  }                                                                     ;
  ///////////////////////////////////////////////////////////////////////
  return true                                                           ;
}
