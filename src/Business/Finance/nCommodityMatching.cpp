#include <business.h>

#pragma message("CommodityMatching requires additional works")

N::CommodityMatching:: CommodityMatching ( QWidget * parent , Plan * p )
                     : TreeWidget        (           parent ,        p )
{
  Configure ( ) ;
}

N::CommodityMatching::~CommodityMatching (void)
{
}

void N::CommodityMatching::Configure(void)
{
  NewTreeWidgetItem ( head                     ) ;
  setWindowTitle    ( tr("Commodity matching") ) ;
  head->setText     ( 0 , tr("Script" )        ) ;
  head->setText     ( 1 , tr("Company")        ) ;
  ////////////////////////////////////////////////
  setFocusPolicy          ( Qt::WheelFocus     ) ;
  setDragDropMode         ( NoDragDrop         ) ;
  setAlternatingRowColors ( true               ) ;
  setRootIsDecorated      ( false              ) ;
  setSelectionMode        ( SingleSelection    ) ;
  setColumnCount          ( 2                  ) ;
  assignHeaderItems       ( head               ) ;
  MountClicked            ( 2                  ) ;
  PassDragDrop = false                           ;
  plan -> setFont ( this )                       ;
}

bool N::CommodityMatching::FocusIn(void)
{
  nKickOut          ( IsNull(plan) , true            ) ;
  DisableAllActions (                                ) ;
  AssignAction      ( Label        , windowTitle ( ) ) ;
  LinkAction        ( Refresh      , startup     ( ) ) ;
  LinkAction        ( Insert       , New         ( ) ) ;
  LinkAction        ( Delete       , Delete      ( ) ) ;
  return true                                          ;
}

void N::CommodityMatching::run(int Type,ThreadData * data)
{
  switch (Type)                                          {
    case 10001                                           :
      List          (                                  ) ;
    break                                                ;
    case 1002                                            :
      LoadScripts   (                                  ) ;
    break                                                ;
    case 1003                                            :
      LoadCompanies ( data->Arguments[0].toULongLong() ) ;
    break                                                ;
  }                                                      ;
}

bool N::CommodityMatching::startup(void)
{
  clear (       ) ;
  start ( 10001 ) ;
  return true     ;
}

void N::CommodityMatching::setScripts(void)
{
  start ( 1002 ) ;
}

void N::CommodityMatching::setCompanies(SUID company)
{
  VarArgs args          ;
  args << company       ;
  start ( 1003 , args ) ;
}

void N::CommodityMatching::List(void)
{
  GroupItems    GI ( plan        )           ;
  SqlConnection SC ( plan -> sql )           ;
  if (SC.open("CommodityMatching","List"))   {
    QString     Q                            ;
    QString     N                            ;
    QStringList L                            ;
    CUIDs       U                            ;
    int         u                            ;
    Q = SC . sql . SelectFrom                (
          "id"                               ,
          Table                              ,
          SC.OrderByAsc("id")              ) ;
    SqlLoopNow ( SC , Q )                    ;
      U << SC . Int ( 0 )                    ;
    SqlLoopErr ( SC , Q )                    ;
    SqlLoopEnd ( SC , Q )                    ;
    foreach (u,U)                            {
      Q = SC . sql . SelectFrom              (
            "script,company"                 ,
            Table                            ,
            QString("where id = %1").arg(u)) ;
      if (SC.Fetch(Q))                       {
        SUID s = SC.Uuid(0)                  ;
        SUID c = SC.Uuid(1)                  ;
        NewTreeWidgetItem ( it )             ;
        it->setData(0,Qt::UserRole,s)        ;
        it->setData(1,Qt::UserRole,c)        ;
        N = SC.getName                       (
              PlanTable(Names)               ,
              "uuid"                         ,
              vLanguageId                    ,
              s                            ) ;
        it->setText(0,N)                     ;
        L = GI.Names(SC,c)                   ;
        if (L.count()>0)                     {
          it->setText(1,L[0])                ;
        }                                    ;
        addTopLevelItem ( it )               ;
      }                                      ;
    }                                        ;
    SC.close()                               ;
  }                                          ;
  SC.remove()                                ;
  Alert ( Done )                             ;
}

void N::CommodityMatching::LoadScripts(void)
{
  MatchingScripts . clear ( )                     ;
  SqlConnection SC ( plan -> sql )                ;
  if (SC.open("CommodityMatching","LoadScripts")) {
    QString N                                     ;
    UUIDs   U                                     ;
    SUID    u                                     ;
    U = SC.Uuids                                  (
          PlanTable(Scripts)                      ,
          "uuid"                                  ,
          QString("where type = %1 %2"            )
          .arg(Scripts::Matching                  )
          .arg(SC.OrderByAsc("id")            ) ) ;
    ScriptUuids = U                               ;
    foreach (u,U)                                 {
      N = SC.getName                              (
            PlanTable(Names)                      ,
            "uuid"                                ,
            vLanguageId                           ,
            u                                   ) ;
      MatchingScripts [ u ] = N                   ;
    }                                             ;
    SC.close()                                    ;
  }                                               ;
  SC.remove()                                     ;
}

void N::CommodityMatching::LoadCompanies(SUID company)
{
  Companies . clear ( )                             ;
  GroupItems    GI ( plan        )                  ;
  SqlConnection SC ( plan -> sql )                  ;
  if (SC.open("CommodityMatching","LoadCompanies")) {
    QStringList L                                   ;
    UUIDs       U                                   ;
    SUID        u                                   ;
    U = GI . Subordination                          (
          SC                                        ,
          company                                   ,
          Types  :: Division                        ,
          Types  :: Organization                    ,
          Groups :: Subordination                   ,
          SC.OrderByAsc("position")               ) ;
    CompanyUuids = U                                ;
    foreach (u,U)                                   {
      L = GI.Names(SC,u)                            ;
      if (L.count()>0) Companies [ u ] = L [ 0 ]    ;
    }                                               ;
    SC.close()                                      ;
  }                                                 ;
  SC.remove()                                       ;
}

void N::CommodityMatching::New(void)
{
  NewTreeWidgetItem ( IT )      ;
  IT->setData(0,Qt::UserRole,0) ;
  setAlignments   ( IT     )    ;
  addTopLevelItem ( IT     )    ;
  scrollToItem    ( IT     )    ;
  doubleClicked   ( IT , 0 )    ;
}

void N::CommodityMatching::Delete(void)
{
  QTreeWidgetItem * item = currentItem ( )   ;
  if (IsNull(item)) return                   ;
  SUID s = nTreeUuid(item,0)                 ;
  SUID c = nTreeUuid(item,1)                 ;
  if (s<=0 || c<=0) return                   ;
  SqlConnection SC ( plan -> sql )           ;
  if (SC.open("CommodityMatching","Delete")) {
    QString Q                                ;
    Q = QString("delete from %1 where script = %2 and company = %3 ;").arg(Table).arg(s).arg(c) ;
    SC.Query(Q)                              ;
    SC.close()                               ;
  }                                          ;
  SC.remove()                                ;
  takeItem ( item )                          ;
  Alert    ( Done )                          ;
}

void N::CommodityMatching::doubleClicked(QTreeWidgetItem * item,int column)
{
  SUID s = nTreeUuid(item,0)                       ;
  SUID c = nTreeUuid(item,1)                       ;
  if (s>0 && c>0) return                           ;
  //////////////////////////////////////////////////
  ComboBox * cc                                    ;
  switch (column)                                  {
    case 0                                         :
      cc = (ComboBox *)setComboBox                 (
           item,column                             ,
           SIGNAL(activated(int))                  ,
           SLOT(scriptFinished(int)) )             ;
      cc->appendNames(ScriptUuids,MatchingScripts) ;
    break                                          ;
    case 1                                         :
      cc = (ComboBox *)setComboBox                 (
           item,column                             ,
           SIGNAL(activated(int))                  ,
           SLOT(companyFinished(int)))             ;
      cc->appendNames(CompanyUuids,Companies)      ;
    break                                          ;
  }                                                ;
  cc -> setEditable        ( true )                ;
  cc -> setMaxVisibleItems ( 30   )                ;
  cc -> showPopup          (      )                ;
}

void N::CommodityMatching::scriptFinished(int)
{
  if (IsNull(ItemEditing)) return                ;
  QComboBox * cc = Casting(QComboBox,ItemWidget) ;
  if (IsNull(cc)) return                         ;
  SUID company = nTreeUuid(ItemEditing,1)        ;
  SUID script  = N::GetUuid(cc)                  ;
  appendMatching   ( script , company        )   ;
  ItemEditing->setData(0,Qt::UserRole,script )   ;
  ItemEditing->setText(0,cc->currentText()   )   ;
  removeOldItem    ( true , 0                )   ;
  Alert            ( Done                    )   ;
}

void N::CommodityMatching::companyFinished(int)
{
  if (IsNull(ItemEditing)) return                ;
  QComboBox * cc = Casting(QComboBox,ItemWidget) ;
  if (IsNull(cc)) return                         ;
  SUID company = N::GetUuid(cc)                  ;
  SUID script  = nTreeUuid(ItemEditing,0)        ;
  appendMatching   ( script , company        )   ;
  ItemEditing->setData(1,Qt::UserRole,company)   ;
  ItemEditing->setText(1,cc->currentText()   )   ;
  removeOldItem    ( true , 0                )   ;
  Alert            ( Done                    )   ;
}

bool N::CommodityMatching::appendMatching(SUID script,SUID company)
{
  if (script <=0) return false                         ;
  if (company<=0) return false                         ;
  SqlConnection SC ( plan -> sql )                     ;
  if (SC.open("CommodityMatching","appendMatching"))   {
    QString Q                                          ;
    Q  = SC.sql.InsertInto(Table,2,"script","company") ;
    SC . Prepare ( Q                   )               ;
    SC . Bind    ( "script"  , script  )               ;
    SC . Bind    ( "company" , company )               ;
    SC . Exec    (                     )               ;
    SC . close   (                     )               ;
  }                                                    ;
  SC.remove()                                          ;
  return true                                          ;
}
