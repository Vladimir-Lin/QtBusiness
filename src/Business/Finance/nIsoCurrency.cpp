#include <business.h>

N::IsoCurrency:: IsoCurrency ( QWidget * parent , Plan * p )
               : TreeWidget  (           parent ,        p )
{
  Configure ( ) ;
}

N::IsoCurrency::~IsoCurrency(void)
{
}

QSize N::IsoCurrency::sizeHint(void) const
{
  if ( plan  -> Booleans [ "Desktop" ] )            {
    return SizeSuggestion ( QSize ( 1024 ,  720 ) ) ;
  } else
  if ( plan  -> Booleans [ "Pad"     ] )            {
    return QSize ( 1024 ,  720 )                    ;
  } else
  if ( plan  -> Booleans [ "Phone"   ] )            {
    return QSize (  320 ,  480 )                    ;
  }                                                 ;
  return   QSize ( 1024 ,  720 )                    ;
}

void N::IsoCurrency::Configure(void)
{
  NewTreeWidgetItem            ( head                               ) ;
  head -> setText              ( 0 , tr("ISO"     )                 ) ;
  head -> setText              ( 1 , tr("Currency")                 ) ;
  head -> setText              ( 2 , tr("Name"    )                 ) ;
  head -> setText              ( 3 , tr("Entity"  )                 ) ;
  head -> setText              ( 4 , ""                             ) ;
  setWindowTitle               ( tr("ISO 4217 currencies standard") ) ;
  setDragDropMode              ( NoDragDrop                         ) ;
  setRootIsDecorated           ( false                              ) ;
  setAlternatingRowColors      ( true                               ) ;
  setSelectionMode             ( SingleSelection                    ) ;
  setColumnCount               ( 5                                  ) ;
  setHorizontalScrollBarPolicy ( Qt::ScrollBarAsNeeded              ) ;
  setVerticalScrollBarPolicy   ( Qt::ScrollBarAsNeeded              ) ;
  assignHeaderItems            ( head                               ) ;
  plan -> setFont              ( this                               ) ;
  /////////////////////////////////////////////////////////////////////
  nConnect ( this , SIGNAL ( sortCurrencies ( ) )                     ,
             this , SLOT   ( SortISO        ( ) )                   ) ;
}

void N::IsoCurrency::run(int T,ThreadData * d)
{
  nDropOut ( ! IsContinue ( d ) ) ;
  switch   ( T                  ) {
    case 10001                    :
      List ( d                  ) ;
    break                         ;
  }                               ;
}

bool N::IsoCurrency::startup(void)
{
  clear (       ) ;
  start ( 10001 ) ;
  return true     ;
}

void N::IsoCurrency::List(ThreadData * d)
{
  nDropOut ( ! IsContinue ( d ) )                ;
  emit assignEnabling ( false )                  ;
  ////////////////////////////////////////////////
  EnterSQL   ( SC , plan->sql )                  ;
    QString          Q                           ;
    TreeWidgetItems Items                        ;
    Q = SC.sql.SelectFrom                        (
          "id,uuid,shortname,currency,entity"    ,
          PlanTable(Currency)                    ,
          SC . OrderByAsc ( "id" )             ) ;
    SqlLoopNow ( SC , Q )                        ;
      int Id = SC.Int(0)                         ;
      if (Id<997)                                {
        NewTreeWidgetItem(it)                    ;
        it->setData(0,Qt::UserRole,Id        )   ;
        it->setData(1,Qt::UserRole,SC.Uuid(1))   ;
        it->setText(0,SC.String(2)           )   ;
        it->setText(1,SC.String(3)           )   ;
        it->setText(3,SC.String(4)           )   ;
        Items << it                              ;
      }                                          ;
    SqlLoopErr ( SC , Q )                        ;
    SqlLoopEnd ( SC , Q )                        ;
    for (int i=0;i<Items.count();i++)            {
      SUID    uuid = nTreeUuid ( Items[i] , 1 )  ;
      QString name                               ;
      name = SC.getName                          (
               PlanTable(Names)                  ,
               "uuid"                            ,
               vLanguageId                       ,
               uuid                            ) ;
      if (name.length()>0)                       {
        Items[i]->setText(2,name)                ;
      }                                          ;
    }                                            ;
    if ( Items . count ( ) > 0 )                 {
      addTopLevelItems(Items)                    ;
    }                                            ;
  LeaveSQL            ( SC , plan->sql         ) ;
  ////////////////////////////////////////////////
  emit assignEnabling ( true                   ) ;
  emit AutoFit        (                        ) ;
  emit sortCurrencies (                        ) ;
  Alert               ( Done                   ) ;
}

void N::IsoCurrency::SortISO(void)
{
  sortItems ( 0 , Qt::AscendingOrder ) ;
}

void N::IsoCurrency::List(void)
{
  List ( &Data ) ;
}

bool N::IsoCurrency::Menu(QPoint)
{
  nScopedMenu ( mm , this )                       ;
  QAction         * aa                            ;
  UUIDs             Uuids                         ;
  mm . add ( 601 , tr("Translations")           ) ;
  mm . setFont   ( plan )                         ;
  aa = mm . exec (      )                         ;
  if (IsNull(aa)) return true                     ;
  switch (mm[aa])                                 {
    case 601                                      :
      for (int i=0;i<topLevelItemCount();i++)     {
        QTreeWidgetItem * it                      ;
        it = topLevelItem  ( i      )             ;
        Uuids << nTreeUuid ( it , 1 )             ;
      }                                           ;
      emit Translations ( windowTitle() , Uuids ) ;
    break                                         ;
    default                                       :
    break                                         ;
  }                                               ;
  return true                                     ;
}
