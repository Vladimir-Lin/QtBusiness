typedef struct {
  int                id   ;
  unsigned long long uuid ;
  const char       * name ;
} private_currency;

private_currency DefaultCurrency[]={
  {840,21498878918393872LL,"USD"},
  {978,21498878918393875LL,"EUR"},
  {826,21498878918393882LL,"GBP"},
  { 36,21471556819492294LL,"AUD"},
  {124,21498878918394010LL,"CAD"},
  {392,21498878918393967LL,"JPY"},
  {156,21498878918394005LL,"CNY"},
  {643,21498878918393920LL,"RUB"},
  {344,21498878918393976LL,"HKD"},
  {554,21498878918393890LL,"NZD"},
  {901,21498878918393895LL,"TWD"},
  {484,21498878918393944LL,"MXN"},
  {710,21498878918393906LL,"ZAR"},
  {764,21498878918393892LL,"THB"},
  {608,21498878918393925LL,"PHP"},
  {702,21498878918393909LL,"SGD"},
  {578,21498878918393902LL,"NOK"},
  {356,21498878918393973LL,"INR"},
  {752,21498878918393900LL,"SEK"},
  {458,21498878918393948LL,"MYR"},
  {348,21498878918393975LL,"HUF"},
  {208,21498878918393982LL,"DKK"},
  {756,21498878918393899LL,"CHF"},
  {784,21471556819492287LL,"AED"},
  {971,21471556819492288LL,"AFN"},
  {  8,21471556819492289LL,"ALL"},
  { 51,21471556819492290LL,"AMD"},
  {532,21471556819492291LL,"ANG"},
  {973,21471556819492292LL,"AOA"},
  { 32,21471556819492293LL,"ARS"},
  {533,21471556819492295LL,"AWG"},
  {944,21471556819492296LL,"AZN"},
  {977,21471556819492297LL,"BAM"},
  { 52,21471556819492298LL,"BBD"},
  { 50,21471556819492299LL,"BDT"},
  {975,21471556819492300LL,"BGN"},
  { 48,21471556819492301LL,"BHD"},
  {108,21471556819492302LL,"BIF"},
  { 60,21471556819492303LL,"BMD"},
  { 96,21471556819492304LL,"BND"},
  { 68,21471556819492305LL,"BOB"},
  {984,21471556819492306LL,"BOV"},
  {986,21471556819492307LL,"BRL"},
  { 44,21471556819492308LL,"BSD"},
  { 64,21471556819492309LL,"BTN"},
  { 72,21471556819492310LL,"BWP"},
  {974,21471556819492311LL,"BYR"},
  { 84,21471556819492312LL,"BZD"},
  {976,21498878918394001LL,"CDF"},
  {947,21498878918393897LL,"CHE"},
  {948,21498878918393898LL,"CHW"},
  {990,21498878918394006LL,"CLF"},
  {152,21498878918394007LL,"CLP"},
  {170,21498878918394004LL,"COP"},
  {970,21498878918394003LL,"COU"},
  {188,21498878918394000LL,"CRC"},
  {931,21498878918393997LL,"CUC"},
  {192,21498878918393998LL,"CUP"},
  {132,21498878918394009LL,"CVE"},
  {203,21498878918393996LL,"CZK"},
  {262,21498878918393995LL,"DJF"},
  {214,21498878918393994LL,"DOP"},
  {233,21498878918393990LL,"EEK"},
  {818,21498878918393993LL,"EGP"},
  {232,21498878918393991LL,"ERN"},
  {230,21498878918393989LL,"ETB"},
  {242,21498878918393987LL,"FJD"},
  {238,21498878918393988LL,"FKP"},
  {981,21498878918393985LL,"GEL"},
  {936,21498878918393984LL,"GHS"},
  {292,21498878918393983LL,"GIP"},
  {270,21498878918393986LL,"GMD"},
  {324,21498878918393980LL,"GNF"},
  {320,21498878918393981LL,"GTQ"},
  {328,21498878918393979LL,"GYD"},
  {340,21498878918393977LL,"HNL"},
  {191,21498878918393999LL,"HRK"},
  {332,21498878918393978LL,"HTG"},
  {360,21498878918393972LL,"IDR"},
  {376,21498878918393969LL,"ILS"},
  {368,21498878918393970LL,"IQD"},
  {364,21498878918393971LL,"IRR"},
  {352,21498878918393974LL,"ISK"},
  {388,21498878918393968LL,"JMD"},
  {400,21498878918393966LL,"JOD"},
  {404,21498878918393964LL,"KES"},
  {417,21498878918393960LL,"KGS"},
  {116,21498878918394011LL,"KHR"},
  {174,21498878918394002LL,"KMF"},
  {408,21498878918393963LL,"KPW"},
  {410,21498878918393962LL,"KRW"},
  {414,21498878918393961LL,"KWD"},
  {136,21498878918394008LL,"KYD"},
  {398,21498878918393965LL,"KZT"},
  {418,21498878918393959LL,"LAK"},
  {422,21498878918393957LL,"LBP"},
  {144,21498878918393905LL,"LKR"},
  {430,21498878918393955LL,"LRD"},
  {426,21498878918393956LL,"LSL"},
  {440,21498878918393953LL,"LTL"},
  {428,21498878918393958LL,"LVL"},
  {434,21498878918393954LL,"LYD"},
  {504,21498878918393870LL,"MAD"},
  {498,21498878918393942LL,"MDL"},
  {969,21498878918393950LL,"MGA"},
  {807,21498878918393951LL,"MKD"},
  {104,21498878918393938LL,"MMK"},
  {496,21498878918393941LL,"MNT"},
  {446,21498878918393952LL,"MOP"},
  {478,21498878918393946LL,"MRO"},
  {480,21498878918393945LL,"MUR"},
  {462,21498878918393947LL,"MVR"},
  {454,21498878918393949LL,"MWK"},
  {979,21498878918393943LL,"MXV"},
  {943,21498878918393939LL,"MZN"},
  {516,21498878918393937LL,"NAD"},
  {566,21498878918393933LL,"NGN"},
  {558,21498878918393934LL,"NIO"},
  {524,21498878918393936LL,"NPR"},
  {512,21498878918393931LL,"OMR"},
  {590,21498878918393929LL,"PAB"},
  {604,21498878918393926LL,"PEN"},
  {598,21498878918393928LL,"PGK"},
  {586,21498878918393930LL,"PKR"},
  {985,21498878918393923LL,"PLN"},
  {600,21498878918393927LL,"PYG"},
  {634,21498878918393922LL,"QAR"},
  {946,21498878918393921LL,"RON"},
  {941,21498878918393912LL,"RSD"},
  {646,21498878918393919LL,"RWF"},
  {682,21498878918393914LL,"SAR"},
  { 90,21498878918393908LL,"SBD"},
  {690,21498878918393913LL,"SCR"},
  {938,21498878918393904LL,"SDG"},
  {654,21498878918393918LL,"SHP"},
  {694,21498878918393910LL,"SLL"},
  {706,21498878918393907LL,"SOS"},
  {968,21498878918393903LL,"SRD"},
  {678,21498878918393915LL,"STD"},
  {222,21498878918393992LL,"SVC"},
  {760,21498878918393896LL,"SYP"},
  {748,21498878918393901LL,"SZL"},
  {972,21498878918393894LL,"TJS"},
  {934,21498878918393885LL,"TMT"},
  {788,21498878918393887LL,"TND"},
  {776,21498878918393889LL,"TOP"},
  {949,21498878918393886LL,"TRY"},
  {780,21498878918393888LL,"TTD"},
  {834,21498878918393893LL,"TZS"},
  {980,21498878918393883LL,"UAH"},
  {800,21498878918393884LL,"UGX"},
  {997,21498878918393880LL,"USN"},
  {998,21498878918393881LL,"USS"},
  {940,21498878918393878LL,"UYI"},
  {858,21498878918393879LL,"UYU"},
  {860,21498878918393877LL,"UZS"},
  {937,21498878918393874LL,"VEF"},
  {704,21498878918393873LL,"VND"},
  {548,21498878918393876LL,"VUV"},
  {882,21498878918393916LL,"WST"},
  {961,21498878918393858LL,"XAG"},
  {959,21498878918393866LL,"XAU"},
  {955,21498878918393865LL,"XBA"},
  {956,21498878918393864LL,"XBB"},
  {957,21498878918393863LL,"XBC"},
  {958,21498878918393862LL,"XBD"},
  {951,21498878918393917LL,"XCD"},
  {960,21498878918393861LL,"XDR"},
  {952,21498878918393891LL,"XOF"},
  {964,21498878918393860LL,"XPD"},
  {953,21498878918393871LL,"XPF"},
  {962,21498878918393859LL,"XPT"},
  {963,21498878918393857LL,"XTS"},
  {999,21498878918393856LL,"XXX"},
  {886,21498878918393869LL,"YER"},
  {894,21498878918393868LL,"ZMK"},
  {932,21498878918393867LL,"ZWL"},
  {  0,                0LL,""   }
};

typedef struct              {
  const char * fromCurrency ;
  const char * toCurrency   ;
} private_currencyexchange  ;

private_currencyexchange DefaultCurrencyExchange[]={
  {"AUD","CAD"},
  {"AUD","CHF"},
  {"AUD","JPY"},
  {"AUD","NZD"},
  {"AUD","USD"},
  {"CAD","CHF"},
  {"CAD","JPY"},
  {"CHF","JPY"},
  {"EUR","AUD"},
  {"EUR","CAD"},
  {"EUR","CHF"},
  {"EUR","GBP"},
  {"EUR","JPY"},
  {"EUR","NZD"},
  {"EUR","NOK"},
  {"EUR","SEK"},
  {"EUR","USD"},
  {"GBP","AUD"},
  {"GBP","CAD"},
  {"GBP","CHF"},
  {"GBP","JPY"},
  {"GBP","NZD"},
  {"GBP","USD"},
  {"NZD","CAD"},
  {"NZD","CHF"},
  {"NZD","JPY"},
  {"NZD","USD"},
  {"USD","CAD"},
  {"USD","SGD"},
  {"USD","NOK"},
  {"USD","CHF"},
  {"USD","JPY"},
  {"USD","SEK"},
  {"XAG","USD"},
  {"XAU","USD"},
  { 0   , 0   }
};
