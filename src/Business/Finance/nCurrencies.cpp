#include <business.h>

typedef struct            {
  int                id   ;
  unsigned long long uuid ;
  const char       * name ;
} private_currency        ;

typedef struct              {
  const char * fromCurrency ;
  const char * toCurrency   ;
} private_currencyexchange  ;

extern private_currency         DefaultCurrency         [ ] ;
extern private_currencyexchange DefaultCurrencyExchange [ ] ;

///////////////////////////////////////////////////////////////////////////////

N::Currencies:: Currencies ( void )
              : Monetary   (      )
{
  clear        ( ) ;
  defaultLists ( ) ;
  defaultPairs ( ) ;
}

N::Currencies::~Currencies(void)
{
}

void N::Currencies::defaultLists(void)
{
  int i = 0                                                  ;
  while ( nGreater    ( DefaultCurrency [ i ] . uuid , 0 ) ) {
    int     id       =  DefaultCurrency [ i ] . id           ;
    SUID    suid     =  DefaultCurrency [ i ] . uuid         ;
    QString name     =  DefaultCurrency [ i ] . name         ;
    ID              << id                                    ;
    Uuids           << suid                                  ;
    ISO             << name                                  ;
    IdMap   [ id   ] =  name                                 ;
    UuidMap [ id   ] =  suid                                 ;
    MapId   [ name ] =  id                                   ;
    MapUuid [ suid ] =  id                                   ;
    UuidIso [ suid ] =  name                                 ;
    IsoUuid [ name ] =  suid                                 ;
    i++                                                      ;
  }                                                          ;
}

void N::Currencies::defaultPairs(void)
{
  int i = 0                                                         ;
  while ( NotNull ( DefaultCurrencyExchange [ i ] . fromCurrency)  &&
          NotNull ( DefaultCurrencyExchange [ i ] . toCurrency  ) ) {
    QString F =     DefaultCurrencyExchange [ i ] . fromCurrency    ;
    QString T =     DefaultCurrencyExchange [ i ] . toCurrency      ;
    if ( ISO . contains ( F ) && ISO . contains ( T ) )             {
      int f = ComposeId ( MapId [ F ] , MapId [ T ] )               ;
      if ( ! Pairs . contains ( f ) ) Pairs << f                    ;
    }                                                               ;
    i++                                                             ;
  }                                                                 ;
}

bool N::Currencies::syncPairs(SqlConnection & SC,QString table)
{
  QString    Q                         ;
  UUIDs      uuids                     ;
  QList<int> FIDs                      ;
  QList<int> TIDs                      ;
  QList<int> PIDs                      ;
  //////////////////////////////////////
  Q = SC.sql.SelectFrom                (
        "uuid,fromcurrency,tocurrency" ,
        table,SC.OrderByAsc("id")    ) ;
  SqlLoopNow ( SC , Q )                ;
    SUID suid = SC . Uuid ( 0 )        ;
    int  fid  = SC . Int  ( 1 )        ;
    int  tid  = SC . Int  ( 2 )        ;
    int  pid  = ComposeId( fid , tid ) ;
    uuids << suid                      ;
    FIDs  << fid                       ;
    TIDs  << tid                       ;
    PIDs  << pid                       ;
  SqlLoopErr ( SC , Q )                ;
  SqlLoopEnd ( SC , Q )                ;
  //////////////////////////////////////
  // Delete items
  int PID                              ;
  foreach (PID,PIDs)                   {
    if (!Pairs.contains(PID))          {
      QPair<int,int> P = DecodeId(PID) ;
      int fid   = P . first            ;
      int tid   = P . second           ;
      int index = Pairs.indexOf(PID)   ;
      QString E                        ;
      E = QString(
            "where fromcurrency = %1 "
            "and tocurrency = %2 ;"    )
          .arg(fid).arg(tid)           ;
      if (SC.Fetch(Q))                 {
        uuids . takeAt ( index )       ;
        FIDs  . takeAt ( index )       ;
        TIDs  . takeAt ( index )       ;
        PIDs  . takeAt ( index )       ;
      }                                ;
    }                                  ;
  }                                    ;
  //////////////////////////////////////
  // Set Uuid Map
  for (int i=0;i<PIDs.count();i++)     {
    if (!Pairs.contains(PIDs[i]))      {
      Pairs << PIDs[i]                 ;
    }                                  ;
    PairUuid[PIDs [i]] = uuids[i]      ;
    UuidPair[uuids[i]] = PIDs [i]      ;
  }                                    ;
  //////////////////////////////////////
  // Check Uuid Code
  uuids.clear()                        ;
  for (int i=0;i<Pairs.count();i++)    {
    if (PairUuid.contains(Pairs[i]))   {
      uuids << PairUuid[Pairs[i]]      ;
    }                                  ;
  }                                    ;
#ifdef QUESTIONABLE_CODE_REQUIRE_SOME_FIXUP
  for (int i=0;i<Pairs.count();i++)    {
    if (!PairUuid.contains(Pairs[i])) {
    SUID suid = Neutrino::UniqueUuid(Uuids);
    Uuids              << suid     ;
    PairUuid[Pairs[i]]  = suid     ;
    UuidPair[suid    ]  = Pairs[i] ;
    };
  };
  // Sync to SQL
  for (int i=0;i<Pairs.count();i++)  {
    SUID suid = PairUuid[Pairs[i]]   ;
    int  fid  = Pairs[i] / 1000      ;
    int  tid  = Pairs[i] % 1000      ;
    Q = Sql.SelectFrom("uuid",table) +
        " where fromcurrency = " + QString::number(fid) +
            " and tocurrency = " + QString::number(tid) + ";";
    if (q.exec(Q) && q.next()) {
      // Already exists
    } else {
      Q = Sql.InsertInto("uuid,fromcurrency,tocurrency",table,":UUID,:FROM,:TTOO");
      q.prepare (Q             );
      SqlBind   (q,":UUID",suid);
      SqlBind   (q,":FROM",fid );
      SqlBind   (q,":TTOO",tid );
      q.exec    (              );
    };
  };
#endif
  return true;
}

int N::Currencies::append(QComboBox * combo,int showLanguage)
{
  QString name                           ;
  int     id                             ;
  combo->clear()                         ;
  switch (showLanguage)                  {
    case 0                               :
      foreach (name,ISO)                 {
        combo->addItem(name,MapId[name]) ;
      }                                  ;
    break                                ;
    case 1                               :
      foreach (id  ,ID )                 {
        combo->addItem(Names[id],id    ) ;
      }                                  ;
    break                                ;
    case 2                               :
      foreach (id  ,ID )                 {
        combo->addItem                   (
          QString ( "%1[%2]"             )
               .arg(IdMap[id],Names[id]) ,
          id                           ) ;
      }                                  ;
    break                                ;
  }                                      ;
  return ID . count ( )                  ;
}

int N::Currencies::indexOf(QComboBox * combo,int currency)
{
  bool at = false                                                 ;
  for (int i=0;!at && i<combo->count();i++)                       {
    if (nEqual(combo->itemData(i,Qt::UserRole).toInt(),currency)) {
      combo->setCurrentIndex(i)                                   ;
      at = true                                                   ;
    }                                                             ;
  }                                                               ;
  return combo->currentIndex()                                    ;
}

int N::Currencies::appendPairs(QComboBox * combo,int showLanguage)
{
  int id                                ;
  combo->clear()                        ;
  switch (showLanguage)                 {
    case 0                              :
      foreach (id,Pairs)                {
        combo->addItem(Pairname(id),id) ;
      }                                 ;
    break                               ;
  }                                     ;
  return Pairs . count ( )              ;
}

int N::Currencies::appendPairs(QTreeWidget * tree,int showLanguage)
{
  int id                                                 ;
  tree->clear()                                          ;
  switch (showLanguage)                                  {
    case 0                                               :
      foreach (id,Pairs)                                 {
        NewTreeWidgetItem      ( it                    ) ;
        it  -> setText         ( 0 , Pairname(id)      ) ;
        it  -> setData         ( 0 , Qt::UserRole , id ) ;
        tree-> addTopLevelItem ( it                    ) ;
      }                                                  ;
    break                                                ;
  }                                                      ;
  return Pairs . count ( )                               ;
}
