/****************************************************************************
 *                                                                          *
 * Copyright (C) 2015 Neutrino International Inc.                           *
 *                                                                          *
 * Author : Brian Lin <lin.foxman@gmail.com>, Skype: wolfram_lin            *
 *                                                                          *
 ****************************************************************************/

#ifndef QT_BUSINESS_H
#define QT_BUSINESS_H

#include <QtManagers>

QT_BEGIN_NAMESPACE

#ifndef QT_STATIC
#    if defined(QT_BUILD_BUSINESS_LIB)
#      define Q_BUSINESS_EXPORT Q_DECL_EXPORT
#    else
#      define Q_BUSINESS_EXPORT Q_DECL_IMPORT
#    endif
#else
#    define Q_BUSINESS_EXPORT
#endif


namespace N
{

class Q_BUSINESS_EXPORT CommodityEdit     ;
class Q_BUSINESS_EXPORT Currencies        ;
class Q_BUSINESS_EXPORT IsoCurrency       ;
class Q_BUSINESS_EXPORT CommodityMatching ;

/*****************************************************************************
 *                                                                           *
 *                               Finance widgets                             *
 *                                                                           *
 *****************************************************************************/

class Q_BUSINESS_EXPORT CommodityEdit : public TreeDock
                                      , public Ownership
                                      , public FinanceManager
                                      , public GroupItems
{
  Q_OBJECT
  public:

    enum CommodityEditMsgIDs                {
         CommodityMsgPage       = 132129001 ,
         CommodityMsgProduct    = 132129002 ,
         CommodityMsgSearch     = 132129003 ,
         CommodityMsgIdentifier = 132129004 ,
         CommodityMsgSearchId   = 132129005 ,
         CommodityMsgExport     = 132129006 ,
         CommodityMsgAllFiles   = 132129007 ,
         CommodityMsgPlainText  = 132129008 ,
    } ;

    explicit CommodityEdit               (StandardConstructor) ;
    virtual ~CommodityEdit               (void);

  protected:

    QPoint dragPoint  ;
    bool   dropAction ;
    int    Sorting    ;

    virtual bool        FocusIn           (void) ;
    virtual void        Configure         (void) ;

    virtual bool        hasItem           (void) ;
    virtual bool        startDrag         (QMouseEvent * event) ;
    virtual bool        fetchDrag         (QMouseEvent * event) ;
    virtual QMimeData * dragMime          (void) ;
    virtual void        dragDone          (Qt::DropAction dropIt,QMimeData * mime) ;
    virtual bool        finishDrag        (QMouseEvent * event) ;

    virtual bool        acceptDrop        (QWidget * source,const QMimeData * mime);
    virtual bool        dropNew           (QWidget * source,const QMimeData * mime,QPoint pos) ;
    virtual bool        dropText          (nDeclDrops,const QString & text  ) ;
    virtual bool        dropAlbums        (nDeclDrops,const UUIDs   & Uuids ) ;
    virtual bool        dropDocuments     (nDeclDrops,const UUIDs   & Uuids ) ;
    virtual bool        dropOrganizations (nDeclDrops,const UUIDs   & Uuids ) ;
    virtual bool        dropPeople        (nDeclDrops,const UUIDs   & Uuids ) ;
    virtual bool        dropPictures      (nDeclDrops,const UUIDs   & Uuids ) ;

    virtual UUIDs       LoadUuids         (SqlConnection & Connection) ;
    virtual SUID        AppendUuid        (SqlConnection & Connection);
    virtual void        LoadNames         (SqlConnection & Connection,UUIDs & Uuids) ;
    virtual bool        AppendName        (SqlConnection & Connection,SUID uuid,QString name);
    virtual void        setProduct        (SqlConnection & Connection,SUID uuid,QString name);

    virtual void        SetupMessages     (void) ;
    virtual void        SetupIcons        (void) ;

    virtual void        run               (int Type,ThreadData * data) ;

    virtual bool        List              (ThreadData * data) ;
    virtual void        Paste             (ThreadData * data) ;
    virtual void        GroupJoin         (ThreadData * data) ;

  private:

  public slots:

    virtual bool        startup           (void) ;
    virtual bool        List              (void) ;
    virtual void        New               (void) ;
    virtual void        Paste             (void) ;
    virtual void        Paste             (QString text);
    virtual void        Export            (void) ;
    virtual void        Copy              (void) ;
    virtual void        SearchIdentifier  (void) ;
    virtual void        SearchProduct     (void) ;

  protected slots:

    virtual bool        Menu              (QPoint pos) ;
    virtual void        doubleClicked     (QTreeWidgetItem * item,int column) ;
    virtual void        editingFinished   (void) ;

  private slots:

  signals:

    void Owners                           (QString name,SUID uuid) ;
    void Manifest                         (QString name,SUID uuid) ;
    void Documents                        (QString name,SUID uuid) ;
    void EditNames                        (QString name,SUID uuid) ;
    void Gallery                          (QString name,SUID uuid) ;
    void People                           (QString name,SUID uuid) ;

};

class Q_BUSINESS_EXPORT Currencies : public Monetary
{
  public:

                 Currencies   (void) ;
    virtual     ~Currencies   (void) ;

    virtual bool syncPairs    (SqlConnection & Connection,QString table) ;

    virtual int  append       (QComboBox   * combo,int showLanguage = 0) ; // 0 - ISO , 1 - language , 2 - mix
    virtual int  indexOf      (QComboBox   * combo,int currency        ) ;
    virtual int  appendPairs  (QComboBox   * combo,int showLanguage = 0) ; // 0 - ISO , 1 - language , 2 - mix
    virtual int  appendPairs  (QTreeWidget * tree ,int showLanguage = 0) ; // 0 - ISO , 1 - language , 2 - mix

  protected:

    void         defaultLists (void) ;
    void         defaultPairs (void) ;

  private:

};

class Q_BUSINESS_EXPORT IsoCurrency : public TreeWidget
{
  Q_OBJECT
  public:

    explicit IsoCurrency   (StandardConstructor) ;
    virtual ~IsoCurrency   (void) ;

    virtual QSize sizeHint (void) const ;

  protected:

    virtual void Configure (void) ;

    virtual void run       (int Type,ThreadData * data) ;

    virtual void List      (ThreadData * data) ;

  private:

  public slots:

    virtual bool startup   (void) ;
    virtual void List      (void) ;

  protected slots:

    virtual bool Menu      (QPoint pos) ;

  private slots:

    void        SortISO    (void) ;

  signals:

    void sortCurrencies    (void) ;
    void Translations      (QString title,UUIDs & Uuids) ;

};

class Q_BUSINESS_EXPORT CommodityMatching : public TreeWidget
{
  Q_OBJECT
  public:

    QString Table ;

    explicit CommodityMatching   (StandardConstructor) ;
    virtual ~CommodityMatching   (void) ;

  protected:

    UUIDs CompanyUuids    ;
    UUIDs ScriptUuids     ;
    NAMEs Companies       ;
    NAMEs MatchingScripts ;

    virtual void Configure       (void) ;
    virtual bool FocusIn         (void) ;

    virtual void run             (int Type,ThreadData * data) ;

  private:

    virtual bool appendMatching  (SUID script,SUID company) ;

  public slots:

    virtual bool startup         (void) ;
    virtual void setScripts      (void) ;
    virtual void setCompanies    (SUID company) ;

    virtual void List            (void) ;
    virtual void LoadScripts     (void) ;
    virtual void LoadCompanies   (SUID company) ;

    virtual void New             (void) ;
    virtual void Delete          (void) ;

  protected slots:

    virtual void doubleClicked   (QTreeWidgetItem * item,int column) ;
    virtual void scriptFinished  (int index) ;
    virtual void companyFinished (int index) ;

  private slots:

  signals:

};

}

QT_END_NAMESPACE

#endif
