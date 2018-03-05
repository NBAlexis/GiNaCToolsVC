#pragma once

#include "mainheader.h"

#ifndef EXAM_DF_FLOOR_H
#define EXAM_DF_FLOOR_H


static floor_test dfloat_floor_tests[] = {

{ "0.6173351962722496d0", "-0.11820538775792844d0",
  "-6", "-0.09189713027532098d0" },

{ "-0.17517225806171177d0", "0.1118228341753209d0",
  "-2", "0.04847341028893004d0" },

{ "-0.9387909021047899d0", "-0.16826318310698907d0",
  "5", "-0.09747498656984459d0" },

{ "0.8036728904567848d0", "0.6774308237913269d0",
  "1", "0.1262420666654578d0" },

{ "0.6882568422881421d0", "0.3302150266778784d0",
  "2", "0.02782678893238538d0" },

{ "0.3618917435888378d0", "0.5454396894763598d0",
  "0", "0.3618917435888378d0" },

{ "-0.478470818234076d0", "9.035797971846054d9",
  "-1", "9.035797971367584d9" },

{ "0.6423779722022549d0", "2.0589504447793393d9",
  "0", "0.6423779722022549d0" },

{ "0.21698095744051404d0", "1.570908384361449d9",
  "0", "0.21698095744051404d0" },

{ "0.24033995915823747d0", "6.968395233824382d9",
  "0", "0.24033995915823747d0" },

{ "-0.8531247643149816d0", "-5.299783511441018d9",
  "0", "-0.8531247643149817d0" },

{ "-0.5134978162655872d0", "2.297671112225289d9",
  "-1", "2.297671111711791d9" },

{ "0.6192405432591311d0", "5.4403538407469436d-11",
  "11382357864", "3.744539199218032d-11" },

{ "-0.20340731452742233d0", "5.44351944436815d-12",
  "-37366875715", "2.4681729170135434d-12" },

{ "-0.29394735220898527d0", "-3.6328318262890404d-12",
  "80914109505", "-3.3847154436219604d-12" },

{ "-0.8359336184185098d0", "6.064791537508077d-11",
  "-13783385847", "1.2432123964511977d-11" },

{ "-0.9762544843227843d0", "2.2086465633336306d-11",
  "-44201480696", "1.1997821346734454d-11" },

{ "-0.2919696169517234d0", "6.922295436251983d-11",
  "-4217815025", "3.3402028237741715d-11" },

{ "0.9452118035872986d0", "-1.1093667270485797d19",
  "-1", "-1.1093667270485797d19" },

{ "0.3379784391207531d0", "-3.0106029588222304d19",
  "-1", "-3.0106029588222304d19" },

{ "0.3907483945162724d0", "-9.823409070968835d19",
  "-1", "-9.823409070968835d19" },

{ "-0.4293216868359586d0", "5.965415751655242d19",
  "-1", "5.965415751655242d19" },

{ "0.13727607148241305d0", "-8.310631671228052d19",
  "-1", "-8.310631671228052d19" },

{ "-0.7478116595122868d0", "7.235991436975452d19",
  "-1", "7.235991436975452d19" },

{ "-0.9425796643098138d0", "-1.7749544068364875d-21",
  "531044437355311857664", "0.0d0" },

{ "0.20835281321620536d0", "2.7983277403481253d-21",
  "74456186890490986496", "0.0d0" },

{ "-0.5404541167071248d0", "9.266841531614177d-22",
  "-583212861537931100160", "0.0d0" },

{ "-0.06796825059990208d0", "-6.350644782153893d-21",
  "10702574767038046208", "0.0d0" },

{ "0.30647600932087793d0", "-9.704243038852408d-21",
  "-31581650221851901952", "0.0d0" },

{ "-0.7939481974521416d0", "-7.44148349933678d-21",
  "106692193501860495360", "0.0d0" },

{ "2.622471924924206d9", "0.3428958732728865d0",
  "7648012499", "0.2776496600055352d0" },

{ "9.96303133513731d9", "-0.6839887200892081d0",
  "-14566075496", "-0.09450688719173875d0" },

{ "9.438132647041376d8", "-0.9350840745499996d0",
  "-1009335193", "-0.15301271996267998d0" },

{ "-5.031281076435459d9", "0.8566679205528436d0",
  "-5873082155", "0.5244045303768723d0" },

{ "-9.504293159523993d9", "-0.17779074115973026d0",
  "53457750935", "-0.058079864158457416d0" },

{ "5.593337221858664d8", "0.6365106532159245d0",
  "878749977", "0.3121177083383602d0" },

{ "-9.849085830660753d9", "5.465582064164139d9",
  "-2", "1.0820782976675239d9" },

{ "6.254242990207708d9", "1.9986128256161973d9",
  "3", "2.5840451335911673d8" },

{ "-9.644949290710447d9", "3.677515142398587d9",
  "-3", "1.3875961364853137d9" },

{ "9.966654669106707d9", "3.622741134738514d9",
  "2", "2.7211723996296782d9" },

{ "-7.024110605080818d9", "-1.3131548351819434d9",
  "5", "-4.583364291711011d8" },

{ "-4.5982831731090415d8", "-4.587607917895467d9",
  "0", "-4.5982831731090415d8" },

{ "6.779683583609543d9", "-8.732134194560264d-11",
  "-77640625218895380480", "0.0d0" },

{ "3.040910010354103d8", "-6.386892985922651d-11",
  "-4761172634419539968", "0.0d0" },

{ "-9.081490496057175d9", "-8.389512916135551d-11",
  "108248125807050637312", "0.0d0" },

{ "-2.3391140718625803d9", "4.078343101769488d-11",
  "-57354519065541566464", "0.0d0" },

{ "9.740679130260033d9", "-4.1307299498162d-11",
  "-235810117064018001920", "0.0d0" },

{ "4.630742761978566d9", "-8.36053471494181d-11",
  "-55388117146413842432", "0.0d0" },

{ "6.607827158404311d8", "1.9791074337467208d19",
  "0", "6.607827158404311d8" },

{ "1.5835379695092866d9", "-5.599741962857091d19",
  "-1", "-5.599741962698737d19" },

{ "-9.972337740404726d9", "-1.4833907125668299d19",
  "0", "-9.972337740404726d9" },

{ "-2.8545208802037845d9", "5.460276762513134d19",
  "-1", "5.4602767622276825d19" },

{ "3.4574292483978963d9", "8.177006210253868d19",
  "0", "3.4574292483978963d9" },

{ "-6.94800692720856d9", "5.400944544004402d19",
  "-1", "5.400944543309601d19" },

{ "2.2301147741459103d9", "4.352417825189536d-22",
  "5123852680777023531125296857088", "0.0d0" },

{ "2.855798499915275d9", "-2.1597757039453335d-21",
  "-1322266240285272897749142994944", "0.0d0" },

{ "6.247757812861889d9", "-8.000803060408911d-21",
  "-780891338743010366964468023296", "0.0d0" },

{ "-8.41352264607702d8", "2.4583479152659926d-21",
  "-342242958933120698647142465536", "0.0d0" },

{ "9.08798064415713d9", "-4.6826703076651156d-21",
  "-1940768844921862497464005689344", "0.0d0" },

{ "-2.450923950975804d9", "-8.516681149015905d-21",
  "287779230910741073293637320704", "0.0d0" },

{ "-6.535114995775952d-11", "-0.4217447234387455d0",
  "0", "-6.535114995775952d-11" },

{ "6.91351782048677d-13", "-0.8578740601420116d0",
  "-1", "-0.8578740601413203d0" },

{ "-9.879448244992307d-11", "-0.6016918305263045d0",
  "0", "-9.879448244992307d-11" },

{ "7.820572196574365d-11", "-0.8508242256358738d0",
  "-1", "-0.8508242255576681d0" },

{ "-4.4420680878896835d-11", "0.6509799475016377d0",
  "-1", "0.650979947457217d0" },

{ "-8.35377304874932d-11", "-0.7623592484047194d0",
  "0", "-8.35377304874932d-11" },

{ "-4.697219220983554d-11", "-2.0199834401398075d9",
  "0", "-4.697219220983554d-11" },

{ "4.027899822164905d-11", "-3.0043885624092436d8",
  "-1", "-3.0043885624092436d8" },

{ "-9.473748837497406d-11", "-6.081705720880249d8",
  "0", "-9.473748837497406d-11" },

{ "-6.257060775257221d-11", "4.479345462936419d9",
  "-1", "4.479345462936419d9" },

{ "-4.076402998599221d-11", "3.0379052042471523d9",
  "-1", "3.0379052042471523d9" },

{ "3.2516054170046405d-11", "9.075782126517027d9",
  "0", "3.2516054170046405d-11" },

{ "7.77186165285192d-12", "-7.011585244893556d-11",
  "-1", "-6.234399079608364d-11" },

{ "-4.129939073543463d-11", "-4.398862671531905d-11",
  "0", "-4.129939073543463d-11" },

{ "-4.986332353670153d-11", "4.056354917830567d-11",
  "-2", "3.126377481990981d-11" },

{ "-6.358815251785654d-11", "3.044610839789864d-11",
  "-3", "2.7750172675839383d-11" },

{ "-1.5218538547762808d-11", "-4.9239841620755075d-11",
  "0", "-1.5218538547762808d-11" },

{ "-3.714719523899548d-11", "-3.338962509681127d-11",
  "1", "-3.757570142184203d-12" },

{ "-3.7559900032627426d-11", "-7.103620895893612d19",
  "0", "-3.7559900032627426d-11" },

{ "3.442771371655891d-11", "3.2650979291930292d19",
  "0", "3.442771371655891d-11" },

{ "-8.026236668129701d-11", "-7.030175018925641d19",
  "0", "-8.026236668129701d-11" },

{ "4.0245932625540036d-11", "9.919022649131396d19",
  "0", "4.0245932625540036d-11" },

{ "6.558019989897738d-11", "9.805879474847002d19",
  "0", "6.558019989897738d-11" },

{ "-8.950419173616613d-11", "7.8967335533488d19",
  "-1", "7.8967335533488d19" },

{ "-4.2555105814142415d-11", "-7.367149245343951d-22",
  "57763327980", "-5.012024424412273d-22" },

{ "-7.125466497249949d-11", "-9.625683307253578d-21",
  "7402556545", "-6.2922712544984485d-21" },

{ "8.076311292972551d-11", "5.7198456178965606d-21",
  "14119806429", "1.262169607592943d-21" },

{ "-7.024787982764915d-11", "1.5125149703168537d-21",
  "-46444419531", "6.648179051963393d-22" },

{ "2.3153240875994985d-11", "-1.5025822462858028d-21",
  "-15408967419", "-1.3907844732195436d-21" },

{ "9.445189938981536d-11", "-1.8886893988697117d-21",
  "-50009228329", "-8.218058303553574d-22" },

{ "-8.982223463756733d19", "0.20677548795071854d0",
  "-434394983311440412672", "0.0d0" },

{ "-2.6872844858317455d19", "0.00946240694180256d0",
  "-2839958693765316083712", "0.0d0" },

{ "-9.566658458393646d19", "-0.38847162936974444d0",
  "246264018659858710528", "0.0d0" },

{ "-4.235085548018657d19", "-0.06527446136754045d0",
  "648812025299173376000", "0.0d0" },

{ "2.8443413501845017d19", "-0.04996947402848739d0",
  "-569215787335074643968", "0.0d0" },

{ "-4.484750058861429d19", "-0.2338784192921971d0",
  "191755616975433072640", "0.0d0" },

{ "-2.986802109112903d19", "5.923385648786668d9",
  "-5042390090", "3.561083576852057d9" },

{ "8.088567504347222d18", "9.070536452627407d9",
  "891740807", "8.158341046664973d9" },

{ "-3.09688480137261d19", "-6.508291621550677d9",
  "4758368219", "-1.75538588669977d9" },

{ "4.226418080435591d19", "7.892147197133178d9",
  "5355219530", "6.335538696917366d8" },

{ "1.4013831972690205d19", "-2.4924246236187544d9",
  "-5622570023", "-6.556610185422871d8" },

{ "6.1838203826708914d19", "8.941814127664919d9",
  "6915621700", "8.062833976289089d9" },

{ "-6.916774706038343d18", "3.120694095597196d-11",
  "-221642189018039718512504602624", "0.0d0" },

{ "9.435687674071892d19", "-3.149833308668829d-11",
  "-2995614926067172775889444274176", "0.0d0" },

{ "-6.212546775235241d19", "3.239266009361982d-11",
  "-1917887187183768183263136317440", "0.0d0" },

{ "4.749482734068419d19", "-5.5235623432819116d-11",
  "-859858627258009608103722483712", "0.0d0" },

{ "3.0587261660909548d19", "4.4929685621578874d-11",
  "680780674018761986414328414208", "0.0d0" },

{ "4.141754743467259d19", "5.235000122629564d-11",
  "791166121575339566219965497344", "0.0d0" },

{ "-1.2481803107227873d19", "7.39878580568375d18",
  "-2", "2.3157685041396265d18" },

{ "-1.5884453212818639d19", "-8.336283910718495d19",
  "0", "-1.5884453212818639d19" },

{ "5.000368279611168d19", "-5.031778160332162d19",
  "-1", "-3.1409880720993677d17" },

{ "-3.6360612893747024d19", "4.7875734964388405d19",
  "-1", "1.1515122070641383d19" },

{ "2.357251757890727d19", "-4.493498319637942d19",
  "-1", "-2.136246561747215d19" },

{ "5.0747068626287395d19", "8.591364094011977d19",
  "0", "5.0747068626287395d19" },

{ "2.1440483442615423d19", "9.668454918695627d-21",
  "2217570813838780736509865871750106972160", "0.0d0" },

{ "8.818664212173065d19", "-8.186497379734964d-21",
  "-10772206724212702608743560617665161592832", "0.0d0" },

{ "-7.376250633760416d19", "-6.382238421048869d-21",
  "11557466435965877316178494055246213414912", "0.0d0" },

{ "-4.374244855009332d19", "3.864539687646209d-21",
  "-11318928536282082575630148538694692241408", "0.0d0" },

{ "7.578656580690454d19", "9.103502086399884d-22",
  "83249902166909342613269419960118328426496", "0.0d0" },

{ "5.759312769216988d19", "-9.830658049049094d-21",
  "-5858522125865295462884970652182979280896", "0.0d0" },

{ "-7.091696063135083d-21", "0.3220521420236615d0",
  "-1", "0.3220521420236615d0" },

{ "-7.472975994693659d-21", "-0.06404310380828848d0",
  "0", "-7.472975994693657d-21" },

{ "2.2994935284804662d-21", "0.8294627436562217d0",
  "0", "2.2994935284804662d-21" },

{ "-6.098532726052559d-21", "-0.5103342535054871d0",
  "0", "-6.098532726052559d-21" },

{ "-7.8237727943808d-21", "0.20193503990844952d0",
  "-1", "0.20193503990844952d0" },

{ "-5.357065560054238d-21", "0.535324456368991d0",
  "-1", "0.535324456368991d0" },

{ "8.67862366495009d-23", "5.869284875063336d9",
  "0", "8.67862366495009d-23" },

{ "-3.913399519946995d-21", "4.645302733766437d9",
  "-1", "4.645302733766437d9" },

{ "6.256033435453117d-21", "3.5904533516671333d9",
  "0", "6.2560334354531166d-21" },

{ "-7.970558626381476d-21", "4.548434922363557d9",
  "-1", "4.548434922363557d9" },

{ "7.442840440717647d-21", "-3.3266294818989463d9",
  "-1", "-3.3266294818989463d9" },

{ "-4.6732789449833775d-21", "5.614289998802058d8",
  "-1", "5.614289998802058d8" },

{ "7.136201304639634d-21", "-1.152382297069954d-12",
  "-1", "-1.1523822899337527d-12" },

{ "-7.575364316308001d-21", "-4.790622052171537d-11",
  "0", "-7.575364316308001d-21" },

{ "9.212759331893804d-21", "-6.41398602124991d-11",
  "-1", "-6.413986020328634d-11" },

{ "-1.9103188467401064d-21", "-5.1860189481412404d-11",
  "0", "-1.9103188467401064d-21" },

{ "-4.473075242507236d-21", "2.3036197131739102d-11",
  "-1", "2.303619712726603d-11" },

{ "5.138595152941494d-21", "2.9424719822474346d-11",
  "0", "5.138595152941494d-21" },

{ "-5.137698996313833d-22", "2.2468745456943227d19",
  "-1", "2.2468745456943227d19" },

{ "-7.229848882029144d-21", "-3.031606285079872d19",
  "0", "-7.229848882029144d-21" },

{ "-6.85451854164106d-21", "1.7676693722776926d19",
  "-1", "1.7676693722776926d19" },

{ "5.372223270507929d-21", "-7.439745956384552d19",
  "-1", "-7.439745956384552d19" },

{ "5.598138480271164d-21", "5.149401801116799d19",
  "0", "5.598138480271163d-21" },

{ "9.285618896860432d-21", "6.546424273112694d19",
  "0", "9.285618896860432d-21" },

{ "7.511556502656318d-21", "4.2351039143592516d-21",
  "1", "3.2764525882970666d-21" },

{ "6.050106800286075d-21", "-1.187392681676287d-21",
  "-6", "-1.0742492897716469d-21" },

{ "4.274671258683056d-21", "8.647095729321104d-21",
  "0", "4.274671258683056d-21" },

{ "7.344809600387072d-21", "6.305446958850813d-21",
  "1", "1.039362641536258d-21" },

{ "9.753544125648588d-21", "9.227661371269332d-21",
  "1", "5.258827543792571d-22" },

{ "-7.227362780459908d-21", "-6.70179577363263d-21",
  "1", "-5.255670068272766d-22" },

};

#endif
