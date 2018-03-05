#include "mainheader.h"

static div_test dfloat_div_tests[] = {

{ "-0.651381628953465d0", "-0.9237050214744277d0",
  "0.7051835962889135d0" },

{ "0.5067986732438687d0", "0.6260017267692811d0",
  "0.8095803119575966d0" },

{ "-0.8399445051045212d0", "0.1829250718359493d0",
  "-4.591740742120902d0" },

{ "-0.5987041550692662d0", "-0.4124053212463479d0",
  "1.4517372211878756d0" },

{ "0.5861382519823647d0", "-0.7560374696447822d0",
  "-0.7752767230673855d0" },

{ "-0.012882644582824954d0", "-0.4671067448591679d0",
  "0.02757965866390787d0" },

{ "-0.7830198970435231d0", "2.1690164135025935d9",
  "-3.610022921767931d-10" },

{ "-0.2339206226652567d0", "2.729373380002701d9",
  "-8.57048817062271d-11" },

{ "-0.2285806315782951d0", "-2.602073870582813d9",
  "8.784555817667759d-11" },

{ "-0.5298716781559242d0", "1.3509547453340487d9",
  "-3.9222015392151683d-10" },

{ "0.7287190523338418d0", "-8.244205871151566d9",
  "-8.839166121309548d-11" },

{ "0.18973054487786212d0", "6.557593452200545d9",
  "2.893295326415727d-11" },

{ "0.5084032300982587d0", "4.5431682148621014d-11",
  "1.119049980221105d10" },

{ "0.6621212705475221d0", "-1.838873437953206d-11",
  "-3.600689731450519d10" },

{ "-0.4041791750277005d0", "7.707875701307648d-11",
  "-5.243716825365141d9" },

{ "-0.09569063343466655d0", "4.789751448902253d-11",
  "-1.9978204392338054d9" },

{ "-0.6471008513340974d0", "1.890250884404079d-11",
  "-3.4233596009563705d10" },

{ "-0.4301276572683971d0", "9.134844738134672d-11",
  "-4.708647706651978d9" },

{ "-0.5061027989171409d0", "4.246468515299164d19",
  "-1.1918204434902915d-20" },

{ "-0.9601783702217944d0", "7.495754288877955d19",
  "-1.2809629734615065d-20" },

{ "-0.6477754868655262d0", "-8.507334914535449d19",
  "7.614317449272521d-21" },

{ "0.1934462826116784d0", "3.6173521417193476d19",
  "5.347731573618163d-21" },

{ "-0.7794308505212441d0", "4.172217291786081d19",
  "-1.8681453913144062d-20" },

{ "-0.8462346361305484d0", "7.378170819620111d19",
  "-1.1469436759043748d-20" },

{ "0.9783005897625496d0", "6.175045007596078d-21",
  "1.584280905740958d20" },

{ "-0.9700832605850568d0", "-1.7695051741124812d-21",
  "5.482229013948009d20" },

{ "0.07062591404368701d0", "-8.855398515753737d-21",
  "-7.975464223100028d18" },

{ "0.4751383409805402d0", "-8.1371029771106d-21",
  "-5.8391585103087485d19" },

{ "-0.5103510786836052d0", "8.302178001281015d-21",
  "-6.14719509271975d19" },

{ "0.7148807879199733d0", "4.338856119331781d-21",
  "1.6476250151158982d20" },

{ "4.180670608983218d9", "-0.8621420131862095d0",
  "-4.849167010818503d9" },

{ "3.202209376555907d9", "0.008113117870009012d0",
  "3.9469528581523615d11" },

{ "7.767843042272955d9", "-0.04145956871894663d0",
  "-1.8735947532235483d11" },

{ "1.1937839884817846d9", "0.45557753834605563d0",
  "2.6203749921818776d9" },

{ "-2.4205138097471213d9", "-0.3737757916008485d0",
  "6.475844247109412d9" },

{ "-7.534066568550288d9", "-0.3609372553147958d0",
  "2.0873618496321087d10" },

{ "6.098867840095913d9", "3.0464612528039427d9",
  "2.0019515542771322d0" },

{ "4.956687716396978d9", "7.035407926465974d9",
  "0.704534515724495d0" },

{ "6.969049109639194d9", "-8.115758334653503d9",
  "-0.8587058438990264d0" },

{ "-8.0699835500126705d9", "-1.1896420666819375d9",
  "6.783539163608158d0" },

{ "-2.229793060172571d9", "-2.658809828346301d9",
  "0.8386433043838396d0" },

{ "3.0672739776038485d9", "-7.988270854370873d9",
  "-0.3839722054398737d0" },

{ "2.477055391151669d9", "-1.3522358047779648d-11",
  "-1.8318220700851785d20" },

{ "1.1318646612469008d9", "-8.457695758685169d-11",
  "-1.3382659929385544d19" },

{ "-7.978772126259147d9", "6.210468872769038d-11",
  "-1.2847294286013678d20" },

{ "-9.057338243339752d9", "7.364415429198257d-11",
  "-1.2298787772658011d20" },

{ "-5.341117220720213d9", "4.7359651161519756d-11",
  "-1.1277779902779204d20" },

{ "5.838003830912871d9", "-5.0625478501901024d-11",
  "-1.153175042225754d20" },

{ "6.407156672927742d9", "5.006339136594536d19",
  "1.279808758079079d-10" },

{ "4.687485139826675d8", "-3.5561755068968083d19",
  "-1.3181253655045475d-11" },

{ "-5.838044723576891d9", "-6.843985743599882d19",
  "8.530182473036721d-11" },

{ "3.9279221543350096d9", "-5.882918042982924d19",
  "-6.67682623765291d-11" },

{ "-9.686323716926361d9", "-3.44800215666902d19",
  "2.8092568614527606d-10" },

{ "7.301304808910639d9", "1.2845297359643038d19",
  "5.684029419085038d-10" },

{ "4.380345662298534d9", "-4.352751895415198d-21",
  "-1.0063393842668593d30" },

{ "8.239490918139045d9", "3.2397577733346748d-21",
  "2.5432428886984834d30" },

{ "3.8980499504872713d9", "8.311650110069505d-21",
  "4.689862901910189d29" },

{ "-9.425472285331268d9", "-3.294031046828316d-21",
  "2.861379310436876d30" },

{ "2.517833161624173d9", "3.6891560299469316d-21",
  "6.824957093669991d29" },

{ "-5.463519676339016d9", "-7.298583081866205d-22",
  "7.485726496576409d30" },

{ "1.39357009199772d-11", "0.417842407627649d0",
  "3.335157146709649d-11" },

{ "8.58494900746665d-11", "-0.6481371063028898d0",
  "-1.3245575548724563d-10" },

{ "-9.310282234439046d-11", "0.9146343299129254d0",
  "-1.0179239866631073d-10" },

{ "-8.800556770159418d-11", "-0.9305573406536135d0",
  "9.45729659601417d-11" },

{ "-1.3361456473382827d-11", "0.06420301636905124d0",
  "-2.081125970247039d-10" },

{ "6.1406425153971765d-12", "-0.3082496074575478d0",
  "-1.992100676476244d-11" },

{ "-3.6962256202372035d-11", "3.089420488573177d9",
  "-1.1964139015418631d-20" },

{ "-6.145126590884831d-11", "-6.225608984106817d9",
  "9.870723661849874d-21" },

{ "9.052281678541901d-11", "-6.9187138778508625d9",
  "-1.3083763598782874d-20" },

{ "-3.4950245360118636d-11", "7.543342567738434d9",
  "-4.633257080169575d-21" },

{ "-3.482822570743636d-11", "-3.87599225187502d9",
  "8.985628309909062d-21" },

{ "-9.42226868788213d-11", "7.501937454180854d9",
  "-1.2559780383974101d-20" },

{ "-4.8165035309367155d-11", "9.484620130429997d-11",
  "-0.5078225026096383d0" },

{ "6.880022773725747d-11", "-9.699156104509544d-11",
  "-0.7093424107822056d0" },

{ "1.5817962388036865d-11", "-7.11651152335492d-11",
  "-0.22227129593095693d0" },

{ "-7.0140750853949335d-12", "-4.4677941652531186d-11",
  "0.15699190307254357d0" },

{ "-2.6947489262085355d-11", "8.365454450205894d-11",
  "-0.3221282169723859d0" },

{ "8.703167674410303d-11", "-4.88739813223768d-11",
  "-1.7807363834354917d0" },

{ "1.165112061543483d-12", "-5.899528740399518d19",
  "-1.9749239520860124d-32" },

{ "7.126386981630328d-12", "5.091741402945837d19",
  "1.3995971942933598d-31" },

{ "-7.132349854872655d-13", "7.70347159367981d19",
  "-9.258617712985763d-33" },

{ "4.507266517270466d-11", "-1.6192737232544485d19",
  "-2.7835111831566513d-30" },

{ "-3.025128309814261d-11", "-5.606736896306867d19",
  "5.395523930874836d-31" },

{ "-5.390258677516223d-11", "6.628750121976767d18",
  "-8.131636550373976d-30" },

{ "-8.484515181627938d-11", "6.226893371743352d-21",
  "-1.3625598954575508d10" },

{ "5.110456708789676d-11", "-7.434814854731122d-21",
  "-6.873683889434922d9" },

{ "-7.784815533665352d-11", "-8.942884975553875d-21",
  "8.705038200698988d9" },

{ "6.06871371776654d-11", "-8.4720755768444d-21",
  "-7.163195916657484d9" },

{ "6.395725883763629d-11", "3.2465500186809204d-21",
  "1.970006883295217d10" },

{ "8.23766365482318d-11", "3.5665958051648335d-21",
  "2.3096712116618633d10" },

{ "-6.882125490660233d19", "0.680553203393516d0",
  "-1.0112545876418106d20" },

{ "-8.955858402134752d19", "0.11144092291315044d0",
  "-8.03641801236189d20" },

{ "4.517225460957592d19", "-0.5804969398143229d0",
  "-7.781652496570381d19" },

{ "-9.741926397385082d19", "-0.9037000739789977d0",
  "1.0780043819728059d20" },

{ "9.654390326446178d19", "-0.061963385089831124d0",
  "-1.558079874501655d21" },

{ "9.50855454738802d19", "0.30375471599023185d0",
  "3.130339727036138d20" },

{ "4.323538184184934d19", "-2.6027608151521606d9",
  "-1.661135421670383d10" },

{ "4.0554081767557594d17", "4.814123702784068d9",
  "8.423979995384136d7" },

{ "5.12727309625028d19", "1.761988796449604d9",
  "2.9099351293162037d10" },

{ "-7.335661993746345d19", "-4.961351435504d9",
  "1.4785612527368061d10" },

{ "3.7135994768593306d18", "3.273427798269768d8",
  "1.1344681189614824d10" },

{ "1.3911083524706402d19", "8.651242909451927d9",
  "1.6079866985942366d9" },

{ "6.473382688386894d19", "-3.700509647679497d-11",
  "-1.7493219325738552d30" },

{ "7.25328632809461d19", "6.793518758100849d-11",
  "1.0676773828651782d30" },

{ "7.053090091571119d19", "8.009021819073383d-11",
  "8.806431360661643d29" },

{ "-1.6322872380348074d19", "-1.234889420758779d-11",
  "1.3218084231637898d30" },

{ "-7.716951191497702d19", "-2.473367210466666d-11",
  "3.12001839388891d30" },

{ "-2.1174708383466066d19", "-9.66632270128099d-11",
  "2.1905650202077337d29" },

{ "4.0902039392392786d18", "-5.029423690873208d19",
  "-0.08132549951322827d0" },

{ "1.4562115759233494d17", "4.2665150414889705d19",
  "0.0034131171735308037d0" },

{ "-3.309692589578652d19", "1.1329455009949342d19",
  "-2.9213166799922274d0" },

{ "3.059130103268258d19", "-7.719433592654628d19",
  "-0.3962894513632647d0" },

{ "5.622979366632147d19", "-8.407251901594788d19",
  "-0.6688248945610293d0" },

{ "-7.457587910839625d18", "1.102755747735572d19",
  "-0.6762683328700153d0" },

{ "1.2026615920578564d19", "-3.77964792582931d-21",
  "-3.1819407935832407d39" },

{ "-2.74643694419756d19", "2.538907641816601d-22",
  "-1.0817396028760112d41" },

{ "8.267361397156658d18", "-4.986401395715489d-21",
  "-1.6579815263689556d39" },

{ "9.876393891158812d19", "-5.792612775193684d-22",
  "-1.7049981199250076d41" },

{ "3.927461252713038d17", "4.810589424292295d-21",
  "8.164199656866003d37" },

{ "7.29943837795987d19", "-4.8820727437034755d-21",
  "-1.4951514983823475d40" },

{ "-7.837850970911807d-21", "0.41514160181315674d0",
  "-1.8879945870708947d-20" },

{ "1.1499234744049124d-21", "0.4643166529612681d0",
  "2.4765932194571437d-21" },

{ "-1.094368243984769d-21", "0.9008053219044149d0",
  "-1.2148776404552516d-21" },

{ "2.4821206327531197d-21", "0.22988631081892086d0",
  "1.0797165885654937d-20" },

{ "-4.56226662576732d-22", "0.6695285124602162d0",
  "-6.814148375851899d-22" },

{ "6.442796853653397d-21", "-0.0419134640377401d0",
  "-1.5371663978553802d-19" },

{ "-5.584403218169678d-21", "-8.092869169805251d9",
  "6.9003997235062955d-31" },

{ "-9.796722996869492d-21", "-3.2988270899833827d9",
  "2.9697594719700335d-30" },

{ "9.441829923771915d-22", "5.464575083746736d9",
  "1.7278250877830762d-31" },

{ "-6.419360319610147d-21", "-7.333962810289677d9",
  "8.752921831841952d-31" },

{ "7.973734412555454d-21", "-9.367577614661436d9",
  "-8.512055880994846d-31" },

{ "8.105484193881594d-21", "-8.664550975192905d9",
  "-9.354765431108951d-31" },

{ "-5.3151708182942476d-21", "-3.406928289732576d-11",
  "1.560106455516696d-10" },

{ "-7.026602845639829d-21", "-9.92483846943868d-11",
  "7.079815824989677d-11" },

{ "-5.901970468193158d-21", "2.074489043942647d-11",
  "-2.8450236868815825d-10" },

{ "-6.40466723844613d-21", "-2.551008177490094d-11",
  "2.510641594550906d-10" },

{ "8.056066940872177d-21", "4.645883100460603d-11",
  "1.7340227394170724d-10" },

{ "7.453765056481805d-21", "6.956136187014756d-11",
  "1.0715381148511711d-10" },

{ "7.357434693258832d-21", "-7.093525088486332d19",
  "-1.0372042956753416d-40" },

{ "-3.3759558579798473d-21", "9.991075630444324d19",
  "-3.3789713769084054d-41" },

{ "6.908026973557955d-21", "-4.20805893397862d19",
  "-1.6416183998227845d-40" },

{ "5.181767322756247d-21", "7.46986056263721d19",
  "6.936899664063931d-41" },

{ "-5.7217313601659264d-21", "5.604979023134118d19",
  "-1.0208301113260054d-40" },

{ "-9.340193892824771d-21", "9.147101848766205d19",
  "-1.021109641857176d-40" },

{ "8.331002176099931d-21", "2.0276444314093977d-21",
  "4.108709617449606d0" },

{ "-3.747505523684784d-21", "4.394623185543803d-21",
  "-0.8527478615259381d0" },

{ "-3.310403953328861d-21", "2.3420390876737627d-21",
  "-1.413470838617356d0" },

{ "6.23845405853013d-21", "-8.933620117412232d-21",
  "-0.6983119918397873d0" },

{ "-4.276770609150315d-21", "6.853299965034864d-21",
  "-0.624045442483205d0" },

{ "-8.847946637724495d-21", "6.33827952828724d-21",
  "-1.3959539963860554d0" },

};
