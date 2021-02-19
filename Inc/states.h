/***
Last modified by: $Author: gorkiewicz $
on: $Date: 2018-01-05 11:24:21 +0100 (Pt, 05 sty 2018) $
in revision: $Revision: 78418 $
***/

#if !defined __STATES_H__
#define __STATES_H__

#define ST_NOTHING 0
#define ST_TEST 1
#define ST_PRACA 2
#define ST_PRZERWA 3
#define ST_PRACAPODTRZ 4
#define ST_PRZERWAPODTRZ 5
#define ST_PRACAPODTRZYMANIA 4
#define ST_PRZERWAPODTRZYMANIA 5
#define ST_PRACA_PODTRZYMANIA ST_PRACAPODTRZYMANIA
#define ST_PRZERWA_PODTRZYMANIA ST_PRZERWAPODTRZYMANIA
// #define ST_PRACARECZNA 6
#define ST_OPOZPODAJNIKA 7
#define ST_OPOZNADMUCHU 8
#define ST_OPOZNIENIE_PODAJNIKA ST_OPOZPODAJNIKA
#define ST_OPOZNIENIE_NADMUCHU ST_OPOZNADMUCHU
#define ST_ALARM_TEMPNOTRISING 9
#define ST_ALARM_TEMPERATURA_NIE_ROSNIE 9
#define ST_ALARM_CZUJNIKCO 10
#define ST_ALARM_CZUJNIK_CO 10
#define ST_ALARM_HIGHTEMPCO 11
#define ST_ALARM_HIGH_TEMP_CO 11
#define ST_ALARM_TEMPERATURA_CO_ZBYT_WYSOKA 11
#define ST_ALARM_HIGHTEMPCWU 12
#define ST_ALARM_TEMPERATURA_CWU_ZBYT_WYSOKA 12
#define ST_ALARM_CZUJNIKCWU 13
#define ST_ALARM_CZUJNIK_CWU ST_ALARM_CZUJNIKCWU
#define ST_ALARM_HIGHTEMPPODAJ 15
#define ST_ALARM_TEMPERATURA_PODAJNIKA_ZBYT_WYSOKA 15
#define ST_ALARM_CZUJNIKPODAJ 14
#define ST_ALARM_RUSZT 16
#define ST_ALARM_TOOLONGROZPALANIE 17
#define ST_ALARM_ROZPALANIE_NIEUDANE ST_ALARM_TOOLONGROZPALANIE
#define ST_ALARM_WYLOTUSZKODZONY 18
#define ST_ALARM_CZUJNIK_SPALIN 18
#define ST_ALARM_CZUJNIK_POWROTU 19
#define ST_ALARM_TERMIKSILNIKA 20
#define ST_ALARM_BRAK_KOMUNIKACJI 21
#define ST_ALARM_CURRENT_CHOOSE 22
#define ST_ALARM_BRAK_PALIWA 22
#define ST_ALARM_KONTAKTRON 23
#define ST_ALARM_HIGHTEMPPODAJLAST 23
#define ST_ALARM_TERMIK 24
#define ST_ALARM_TOOLONGPRZEJSCIE 25
#define ST_ALARM_FAZA_PRZEJSCIA_NIEUDANA 25
#define ST_ALARM_FIREOFF 26
#define ST_ALARM_CZUJNIKFLOOR 27
#define ST_ALARM_CZUJNIK_PODLOGOWY 27
#define ST_ALARM_ZWARCIEWENTYLATORA 28
#define ST_ALARM_CZUJNIK_ZAWORU 29

#define ST_PRACA_RECZNA 30
#define ST_ROZPALANIE 31
#define ST_PODSYP 32
#define ST_OFF 33
#define ST_WYGASZONY 33
#define ST_WYLACZANIE 34
#define ST_PRACAROZPALANIA 35
#define ST_PRZERWAROZPALANIA 36
#define ST_RUSZTAOCZYSC 37
#define ST_WYLACZANIE_DOSYP 38
#define ST_WYLACZANIE_RUSZTAWSTEPNIE 39
#define ST_WYLACZANIE_2NDPHASE 40
#define ST_WYLACZANIE_DOSYP_CZEKAJ 41
#define ST_STANDBY 42
#define ST_PRACAPRZEJSCIA 43
#define ST_PRZERWAPRZEJSCIA 44
#define ST_OPOZNIENIEROZPALANIA 45
#define ST_PRACAMODULACJI 46
#define ST_PRZERWAMODULACJI 47
#define ST_TEST_PODAJNIKA_WAIT 48
#define ST_TEST_PODAJNIKA 49
#define ST_TEST_NADMUCHU 50
#define ST_TEST_POMPYCO 51
#define ST_TEST_POMPYCWU 52
#define ST_TESTZAPIS_WAIT 53
#define ST_ZAPISTESTU 54
#define ST_SET_SERVICE_CODE 55
#define ST_DOSYP_CZEKAJ 56
#define ST_WYLACZANIE_DOSYP2 57
#define ST_WYGASZANIE 58
#define ST_WYDMUCH 59
#define ST_WYDMUCHOFF 60
#define ST_PRETESTOGNIA 61
#define ST_TESTOGNIA 62
#define ST_TEST_OGNIA ST_TESTOGNIA
#define ST_PRACAMIEKKISTART 63
#define ST_PRZERWAMIEKKISTART 64
#define ST_PRACA_WAIT 65
#define ST_KALIBRACJA_WENTYLATORA 66
#define ST_CHIMNEY_TEST 67
#define ST_TEST_CZUJNIKA_SPALIN 67
#define ST_CHIMNEY_TEST2 68
#define ST_PRZERWAPODTRZ_T2 69
#define ST_PRACAPODTRZ_T2 70
#define ST_OPOZPODAJNIKA_T2 71
#define ST_OPOZNADMUCHU_T2 72
#define ST_PRACA_NOPID 73
#define ST_PRZERWA_PODTRZYMANIA_NOPID 74
#define ST_PRACA_PODTRZYMANIA_NOPID 75
#define ST_PREALARM_SLIMAK 76
#define ST_BLEDNY_WENTYLATOR 77
#define ST_ROZPALANIE2 78
#define ST_ROZPALANIE3 79
#define ST_PODTRZYMANIE 80
#define ST_KOMUNIKAT 81
#define ST_NADZOR 82
#define ST_PALENIE_RECZNE 83
#define ST_PALENIE_RECZNE_PRZEDMUCH_PRACA 84
#define ST_PALENIE_RECZNE_PRZEDMUCH_PRZERWA 85
#define ST_MALY_DOSYP_PALIWA 86
#define ST_TEST_OGNIA_PRACA 87
#define ST_TEST_OGNIA_PRZERWA 88
#define ST_DOSUN_PODAJNIK 89
#define ST_WROC_PODAJNIK 90
#define ST_PRACA_NADMUCHU_NADZOR 91
#define ST_PRZERWA_NADMUCHU_NADZOR 92
#define ST_MIEKKI_START 93
#define ST_FAZA_PRZEJSCIA 94
#define ST_PODTRZYMANIE_WYL 95
#define ST_WSTRZYMANIE 96
#define ST_POMIAR_ZUZYCIA_PALIWA 97
#define ST_SOLAR_PRACA_NORMALNA 98
#define ST_SOLAR_PRACA_NORMAL_WYCHLADZANIE 99
#define ST_SOLAR_PRACA_NORMAL_PROBKOWANIE 100
#define ST_SOLAR_CZUJNIK_ZBIORNIKA 101
#define ST_SOLAR_PRZEKROCZENIE_MAKS_KOLEKTORA 102
#define ST_SOLAR_CZUJNIK_KOLEKTORA 103
#define ST_SOLAR_PRZEGRZANIE_KOLEKTORA 104
#define ST_SOLAR_ODMRAZANIE 105
#define ST_SOLAR_ANTYZAMARZANIE 106
#define ST_KOMINEK_PRZEWIETRZANIE 107
#define ST_NADZOR_WYGASZANIE 108
#define ST_KOMINKOWY 109
#define ST_URLOP 110
#define ST_PARTY 111
#define ST_TYGODNIOWY 112
#define ST_SOLAR_PRACA_NORMAL_SCHLADZANIE_REWERS 113 // schładzanie rewersyjne
#define ST_PRACA_ANTYLEGIONELLA 114
#define ST_PALNIK_PELLET 115

#define ST_ALARM_CZUJNIK_MOSFETA 200
#define ST_ALARM_HALLOTRON_RUSZT 201
#define ST_ALARM_CZUJNIK_POMPY_DODATKOWEJ 202
#define ST_ALARM_TEMPERATURA_MOSFETA 203
#define ST_ALARM_TIMEOUT_ZAWORU 205
#define ST_ALARM_CZUJNIK_POGODOWY 206
#define ST_ALARM_TEMPERATURA_PODLOGOWA 207
#define ST_ALARM_DRUGI_CZUJNIK_BUFORA 208
#define ST_ALARM_CZUJNIK_POKOJOWKI 209
#define ST_ALARM_CZUJNIK_BUFORA 210
#define ST_ALARM_HALLOTRON_PODAJNIKA 211
#define ST_ALARM_CZUJNIK1_SOLARA 212
#define ST_ALARM_CZUJNIK2_SOLARA 213
#define ST_ALARM_CZUJNIK3_SOLARA 214
#define ST_ALARM_CZUJNIK4_SOLARA 215
#define ST_ALARM_NIEPRAWIDLOWY_NADMUCH 216
#define ST_ALARM_ZBYT_DUZE_OBCIARZENIE_MOSFETA 217
#define ST_ALARM_ZBYT_DUZE_OBCIAZENIE_MOSFETA 217
#define ST_ALARM_NARASTANIE_TEMPERATURY 218
#define ST_ALARM_ZABLOKOWANY_PELLET 219
#define ST_ALARM_SONDA_BRAK_KOMUNIKACJI 220 //sygnalizuje brak komunikacji z zewnętrznym sterownikiem sondy LC-1
#define ST_ALARM_TEMPERATURA_BUFORA_ZBYT_WYSOKA 221
#define ST_ALARM_BLAD_PRZEPUSTNICY 222
#define ST_ALARM_TIMEOUT_M1 223
#define ST_ALARM_CZUJNIK_SAUNY 224
#define ST_ALARM_TEMPERATURA_SAUNY_ZBYT_WYSOKA 225
#define ST_ALARM_CZUJNIK_KOMORY 226
#define ST_ALARM_CZUJNIK_PAROWNIKA 227
#define ST_ALARM_KOMPRESOR_PRACUJE_ZBYT_DLUGO 228
#define ST_ALARM_BRAK_PRZEPLYWU 229
#define ST_ALARM_UJEMNA_ROZNICA_TEMPERATUR 230
#define ST_ALARM_TEMPERATURA_NIE_MALEJE 231
#define ST_ALARM_WENTYLATOR_PAROWNIKA_USZKODZONY 232
#define ST_ALARM_WENTYLATOR_NAWIEWU_USZKODZONY 233
#define ST_ALARM_WENTYLATOR_WYWIEWU_USZKODZONY 234
#define ST_ALARM_CZUJNIK_ZEWNETRZNY 235
#define ST_ALARM_CZUJNIK_WYWIEWU 236
#define ST_ALARM_CZUJNIK_NAWIEWU 237
#define ST_ALARM_CZUJNIK_WYRZUTU 238
#define ST_ALARM_HALLOTRON_WENTYLATORA 239 // sygnalizacja uszkodzenia hallotronu wentylatora - w nowszych projektach nie ma tego alarmu, bo jest tylko warning
#define ST_ALARM_CZUJNIK_C1 241
#define ST_ALARM_CZUJNIK_C2 242
#define ST_ALARM_CZUJNIK_C3 243
#define ST_ALARM_CZUJNIK_C4 244
#define ST_ALARM_AGREGATU 245
#define ST_ALARM_INSTLACJI 246
#define ST_ALARM_CZUJNIK_KONTROLNY 247
#define ST_ALARM_CZUJNIK_POMIESZCZENIA_SAUNY 248
#define ST_ALARM_NAGRZEWNICA_PIERWOTNA 249
#define ST_ALARM_NAGRZEWNICA_WTORNA 250
#define ST_ALARM_CHLODNICA 251
#define ST_ALARM_UZYTKOWNIKA 252
#define ST_ALARM_BLAD_WYMIENNIKA 253
#define ST_ALARM_DRZWI_OTWARTE 254
#define ST_ALARM_CZUJNIK_ZAPALARKI 255
#define ST_ALARM_BRAK_WODY 256
#define ST_ALARM_ZABLOKOWANIE_PODAJNIKA_PRZY_PROBIE_ODBLOKAWANIA_1 257
#define ST_ALARM_ZABLOKOWANIE_PODAJNIKA_PRZY_PROBIE_ODBLOKAWANIA_2 258
#define ST_ALARM_ZABLOKOWANIE_PODAJNIKA_PRZY_PROBIE_ODBLOKAWANIA_3 259
#define ST_ALARM_CZUJNIK_PRZEPLYWU 260
#define ST_ALARM_CZUJNIK_CISNIENIA 261
#define ST_ALARM_ANODA 262
#define ST_ALARM_TEMPERATURA_KOLEKTORA_ZA_WYSOKA 263
#define ST_ALARM_PRESOSTATU 264
#define ST_ALARM_CZUJNIK_ZAWORU_2 265
#define ST_ALARM_CZUJNIK_MOSFETA_2 266
#define ST_ALARM_BLAD_KLAPY_WENTYLATORA 267
#define ST_ALARM_GRZALKA_USZKODZONA 268
#define ST_ALARM_PODAJNIK_ZABLOKOWANY 269
#define ST_ALARM_TEMPERATURA_MOSFETA_2 270
#define ST_ALARM_BRAK_PODLACZENIA_RUSZTU 271
#define ST_ALARM_BRAK_OBROTOW 272
#define ST_ALARM_PRACY_RECZNEJ 273
#define ST_ALARM_CZUJNIK_CZADU 274

#define ST_ALARMY_START 9
#define ST_ALARMY_STOP 29
#define ST_ALARMY2_START 200
#define ST_ALARMY2_STOP 400


#endif
