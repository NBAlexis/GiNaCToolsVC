#include "mainheader.h"

static mul_test lfloat_mul_tests[] = {

{ "0.49162375558276684976L0", "-0.27595139770835290185L0",
  "-0.13566426249969417521L0" },

{ "-0.43085705615141429406L0", "0.76537655129782028376L0",
  "-0.32976788773950077688L0" },

{ "-0.34725675573811781168L0", "-0.44040731024013641718L0",
  "0.15293441375734052306L0" },

{ "-0.47158645084591665022L0", "-0.5531952534025612003L0",
  "0.26087938617692133303L0" },

{ "-0.86377959068682791106L0", "-0.8711108145957097161L0",
  "0.7524477428743513754L0" },

{ "0.07688091831246728666L0", "-0.727039245375017451L0",
  "-0.055895444833634576195L0" },

{ "-0.65693719777446694155L0", "-5.4929597366864347663L9",
  "3.6085295769067602507L9" },

{ "0.9553509506606886749L0", "2.7316499794256227606L9",
  "2.609684404716519364L9" },

{ "0.86245066819702621825L0", "-5.6471738746979076876L9",
  "-4.8704088816580000957L9" },

{ "-0.0011095142242845852372L0", "3.5868904614046262004L9",
  "-3979705.9878791318615L0" },

{ "-0.07537979049336559763L0", "8.268739091555253606L9",
  "-6.2329582036573719373L8" },

{ "-0.67924101443000006024L0", "-4.2094803212494913754L9",
  "2.8592516836286270604L9" },

{ "0.30774277681107480866L0", "-2.7334742019139702906L-11",
  "-8.412069412384417957L-12" },

{ "-0.35713749207523871768L0", "-6.5398928539622633783L-11",
  "2.3356409323048581577L-11" },

{ "-0.14801577485738927266L0", "-9.963460779718656755L-11",
  "1.474749367571264873L-11" },

{ "0.3104124542612814659L0", "-2.9286317751062608258L-11",
  "-9.09083776938307737L-12" },

{ "-0.11446530018625016218L0", "6.4232974401995419684L-11",
  "-7.352446696780128213L-12" },

{ "-0.96939447601348607505L0", "4.1094462170225605183L-11",
  "-3.9836744622561876338L-11" },

{ "0.051486415762180288123L0", "9.676829213398296352L19",
  "4.9822525214063672425L18" },

{ "0.6313327973134614946L0", "3.2653448877462378072L19",
  "2.06151932217404323L19" },

{ "-0.37403303660944479204L0", "9.102796469067070187L19",
  "-3.4047466049628882508L19" },

{ "0.8707828063294901403L0", "-5.5603708853312765524L19",
  "-4.8418753637615606188L19" },

{ "-0.21026381134874289964L0", "-8.2572592232280544185L18",
  "1.7362027955704909688L18" },

{ "-0.77817271482774886984L0", "-5.862569134483721118L19",
  "4.5620913392465632268L19" },

{ "0.10774233598980040668L0", "8.42277329172514105L-21",
  "9.074892699629673044L-22" },

{ "0.25190108887664378198L0", "9.9261121984538427104L-21",
  "2.5003984711022594346L-21" },

{ "-0.6756036645959631085L0", "9.531794528346356556L-21",
  "-6.4397153135265482465L-21" },

{ "-0.6857203923976410447L0", "-1.6874445000752253093L-21",
  "1.1571151047408247225L-21" },

{ "-0.44633489376857998266L0", "2.2805928928283052886L-21",
  "-1.0179081865499001544L-21" },

{ "0.6194914893234261562L0", "6.122106446320417613L-21",
  "3.7925928402275834338L-21" },

{ "6.0914569120648219218L9", "-0.13082334282848865785L0",
  "-7.969047559320230858L8" },

{ "3.6214037646489572409L9", "-0.42724054260765242458L0",
  "-1.5472105094100157093L9" },

{ "-2.3587970682548096273L9", "0.30389573937962490564L0",
  "-7.168283791037869264L8" },

{ "-1.2092840284272862272L9", "-0.9464357317324953064L0",
  "1.1445096143169982957L9" },

{ "9.742195251878672378L9", "-0.8436238049826486367L0",
  "-8.2187478272737786206L9" },

{ "-1.6670311480587791415L9", "-0.7664626357070004785L0",
  "1.277717087546798815L9" },

{ "-9.63709082566058824L8", "3.5038182805272664595L9",
  "-3.376661500605117691L18" },

{ "-6.819958133674458717L9", "5.570090504807835795L9",
  "-3.7987784043567071428L19" },

{ "5.7990616985027046753L9", "5.7633314369957429715L9",
  "3.3421914592058566914L19" },

{ "-8.4466610113280742876L9", "-8.965949996407538079L9",
  "7.5732340264172639616L19" },

{ "-7.670563670654851578L9", "-6.431751468798164421L9",
  "4.9335159155244181172L19" },

{ "8.268803418474998627L9", "-6.6310260568279516366L9",
  "-5.4830650926695757004L19" },

{ "-9.461472353405244053L9", "-3.3101188730107237675L-11",
  "0.31318598203475886787L0" },

{ "6.8579221981166585744L9", "-8.515361268298587097L-11",
  "-0.5839768506684770405L0" },

{ "1.6137913170162297342L9", "-8.897666779537493419L-11",
  "-0.14358977390521366923L0" },

{ "8.022366744559274285L9", "6.8759798363047156095L-11",
  "0.5516163197503107306L0" },

{ "6.268637730252729325L8", "3.8798987053952144677L-13",
  "2.4321679414199160154L-4" },

{ "8.165455714479826517L9", "-7.748491839935670887L-11",
  "-0.6326996697300302909L0" },

{ "-9.245309913477613381L9", "-2.7267702243723164598L19",
  "2.5209835787164953515L29" },

{ "9.113617507957836761L9", "-3.6781774780542862056L19",
  "-3.3521502661371744663L29" },

{ "3695599.756951605604L0", "-4.4160607831464309996L19",
  "-1.6319993156879467502L26" },

{ "-3.1080975558777002585L9", "4.5635619314557275256L19",
  "-1.41839956852540638L29" },

{ "4.379846040113489209L9", "-2.380244519018666713L19",
  "-1.0425104531125744157L29" },

{ "7.799437686108443071L9", "-8.213835920178370665L19",
  "-6.40633014233504056L29" },

{ "-5.0032293022496024175L9", "3.9947928432298324106L-21",
  "-1.9986864609664499789L-11" },

{ "5.1002825856458055377L9", "-8.630588067810955288L-21",
  "-4.4018438026138695895L-11" },

{ "-1.4798783656292287931L9", "-2.1821599778945012917L-21",
  "3.2293313416280286032L-12" },

{ "6.2153176651245460436L9", "-4.842239650508967686L-21",
  "-3.009605763857489489L-11" },

{ "1.1476929860538426329L9", "8.143327858153323155L-21",
  "9.34604026593943011L-12" },

{ "-6.8097130569212408313L9", "-4.5006072118169309446L-21",
  "3.0647843694383655263L-11" },

{ "-8.088711469864653681L-11", "0.55856748494727835656L0",
  "-4.518091222186502735L-11" },

{ "4.4880121763658923538L-11", "0.14537105272497022953L0",
  "6.52427054720794526L-12" },

{ "2.0273639671422034382L-11", "0.5267742506127895251L0",
  "1.0679631345107062621L-11" },

{ "-9.078881981481347403L-11", "0.86040896737522678964L0",
  "-7.811551470607918988L-11" },

{ "-7.2713602444015266416L-11", "0.029963115152720655096L0",
  "-2.1787260431991794891L-12" },

{ "5.8587076221559354985L-11", "0.39205420166003709617L0",
  "2.2969309395639195554L-11" },

{ "9.465227148840012531L-12", "-8.4020295562921954743L9",
  "-0.07952711826157309293L0" },

{ "-9.156088652050785426L-11", "-7.272635024207867507L9",
  "0.66588891015656744834L0" },

{ "3.6865969618651574387L-11", "4.532198690564411727L9",
  "0.16708389923204005057L0" },

{ "-7.773548969171738747L-11", "6.487140494299404015L9",
  "-0.5042810430233337584L0" },

{ "3.181536837232243521L-12", "-8.8275599983550392825L8",
  "-0.0028085207317644360498L0" },

{ "3.512130320642090343L-11", "-6.775467122704530228L9",
  "-0.23796323518164203024L0" },

{ "-7.489684894543042722L-11", "1.3562671200654034619L-11",
  "-1.015801336211924759L-21" },

{ "-6.615171167169027831L-11", "6.4492881876773102747L-11",
  "-4.2663145267886736825L-21" },

{ "5.9969037329081164062L-12", "6.979117807067958578L-11",
  "4.1853097629611348155L-22" },

{ "-9.1419010578306515213L-11", "-3.0321662473944421986L-11",
  "2.7719763824573648138L-21" },

{ "8.653994294784604749L-11", "-2.618325063862645785L-12",
  "-2.2658970164558872502L-22" },

{ "3.778177082827084054L-11", "5.7986141594804582746L-11",
  "2.1908191129505701787L-21" },

{ "9.107023861930220456L-11", "-8.1609888558011610015L18",
  "-7.432232024672778029L8" },

{ "-6.185675579794400257L-11", "8.145498215172660237L19",
  "-5.0385409394852397568L9" },

{ "-5.0086846264250856304L-12", "7.333671928137704804L19",
  "-3.6732049841708537418L8" },

{ "-6.133300578664362783L-11", "-4.647031661618042392L19",
  "2.8501641979273554706L9" },

{ "4.014159298839782726L-12", "7.077385833663047478L18",
  "2.8409754155675469803L7" },

{ "3.9529027598797003857L-11", "3.1931221840357166776L19",
  "1.2622101493907881026L9" },

{ "5.2407793550579649295L-11", "8.178146405814506225L-21",
  "4.2859860846234161862L-31" },

{ "-4.5792905534935737864L-11", "-1.1970719995732820388L-21",
  "5.481740499497593831L-32" },

{ "4.113879746633747024L-11", "5.1093090279978304893L-21",
  "2.1019082929573231173L-31" },

{ "1.9918804321687295055L-11", "1.8243807936344826748L-21",
  "3.6339484036649830696L-32" },

{ "-6.1549842617771214656L-11", "7.210193834294849238L-22",
  "-4.4378629574447235495L-32" },

{ "-3.483482946766538465L-12", "7.8771698631837073084L-22",
  "-2.743998688718375137L-33" },

{ "-3.0540130142847980374L19", "-0.08015004741507677209L0",
  "2.4477928790118809798L18" },

{ "-7.721729897125586787L19", "-0.71282981020428696123L0",
  "5.5042792570168003116L19" },

{ "6.855667806362567159L18", "0.83087248440613607433L0",
  "5.69618574253563119L18" },

{ "-1.0247670372283575993L17", "-0.21215039186338500874L0",
  "2.1740472851667611836L16" },

{ "-4.2451902701279432204L19", "0.363650960045267158L0",
  "-1.5437675173068535736L19" },

{ "-2.3286355030172533736L19", "0.49713327148260372132L0",
  "-1.1576421857055056984L19" },

{ "-6.1529172975127592432L19", "-7.1685660040728041152L9",
  "4.4107593764821477366L29" },

{ "6.7120643409032119372L19", "-2.1673488299796731996L9",
  "-1.45473847960048627434L29" },

{ "8.1354429987417636456L19", "-7.205222753181797397L9",
  "-5.861767900174770815L29" },

{ "7.1263614941049137416L19", "5.4835530180135407083L8",
  "3.907778107845448494L28" },

{ "5.0833800113097826724L19", "-6.2188724451883454807L9",
  "-3.1612891880755627472L29" },

{ "-7.0947371956905508468L19", "-2.434705753418370145L9",
  "1.7273597469339097183L29" },

{ "6.6532780031620346828L19", "-5.126482819920582625L-11",
  "-3.4107915379365690604L9" },

{ "3.3916052110984390742L19", "1.2477416554656457027L-11",
  "4.2318471007818771302L8" },

{ "-2.0596546301412947634L18", "1.4681903489886446838L-11",
  "-3.0239650502232254483L7" },

{ "5.4448198096650564945L18", "-8.328351500006325204L-11",
  "-4.534637322908812735L8" },

{ "-9.0101064221252591136L19", "-8.313725422339249255L-11",
  "7.4907550819604901853L9" },

{ "9.807792586975021252L19", "-8.1013942555768171325L-11",
  "-7.9456794524008327797L9" },

{ "-6.569928333884882197L17", "1.8031274577764523257L19",
  "-1.1846418174451330701L37" },

{ "9.966374081256518232L19", "1.1925741835931471136L18",
  "1.1885640433338393863L38" },

{ "-5.1958776350000747272L19", "9.541066943279536452L19",
  "-4.957421634462466998L39" },

{ "3.0864687811444473814L19", "-7.292720897062086383L17",
  "-2.2508755378381858676L37" },

{ "-4.9023499593352016396L19", "-7.837521201177228469L19",
  "3.8422271741879966693L39" },

{ "1.1092141282192635266L19", "-8.705681388875638857L19",
  "-9.656464792316359058L38" },

{ "9.719341608862581484L18", "3.910223765755272544L-21",
  "0.038004800546468552602L0" },

{ "9.0834836835472717744L19", "2.3217130663560934873L-22",
  "0.021089242756124079488L0" },

{ "-8.9569500426805542816L19", "-6.8114530414478270673L-22",
  "0.061009844610312705923L0" },

{ "-6.250871904307721917L18", "-1.7897852706103755451L-21",
  "0.01118771846280218958L0" },

{ "-4.8350255195162635852L19", "-5.4114390027140489403L-21",
  "0.26164445675428065787L0" },

{ "-3.787718813779143278L19", "4.715777953310022763L-22",
  "-0.017862040875357275534L0" },

{ "-9.6946973380533561685L-21", "0.29842171245928506197L0",
  "-2.8931081813963549629L-21" },

{ "-1.5138229787560283214L-21", "-0.63587548364028950173L0",
  "9.626029187622732088L-22" },

{ "6.9088409628577453984L-21", "0.6675889882861618064L0",
  "4.6122661486241942486L-21" },

{ "-5.9331491274547789645L-21", "0.1840021396402183602L0",
  "-1.0917121342561739605L-21" },

{ "6.5714942924276749333L-21", "0.042451475976117785684L0",
  "2.789696320821885891L-22" },

{ "8.381861494201174241L-21", "-0.14355711097860731382L0",
  "-1.2032758207303532943L-21" },

{ "2.014342763215141127L-21", "-1.2338457666735291661L9",
  "-2.4853882910224610282L-12" },

{ "-5.670580024618139724L-21", "-8.0192486381311308156L8",
  "4.5473791139832611237L-12" },

{ "-1.9225557816894129732L-21", "7.9269598913745234357L9",
  "-1.5240022570382171054L-11" },

{ "4.0368254062037218916L-21", "-9.5325393449487114215L8",
  "-3.848119701332554298L-12" },

{ "4.2776037356780859957L-21", "-5.1221437260809706463L9",
  "-2.1910501137364030878L-11" },

{ "-6.7334467986153699064L-21", "-7.7745493828541701813L9",
  "5.2349514652656512034L-11" },

{ "-4.315187380180362795L-21", "1.3410692406986483366L-11",
  "-5.786965063410868682L-32" },

{ "3.343397258359340776L-21", "3.0757040339096610197L-12",
  "1.0283300434498325547L-32" },

{ "8.5537743863632264L-21", "7.5263454541513394514L-11",
  "6.4378660968641032133L-31" },

{ "-2.842610565794174946L-21", "3.153716909493170071L-11",
  "-8.9647890084490369953L-32" },

{ "2.8400800161467519014L-22", "2.0497242686367281441L-11",
  "5.8213809339661880995L-33" },

{ "9.982896581447590365L-21", "1.6568727649785948007L-11",
  "1.654038946139843086L-31" },

{ "4.678227176611232891L-21", "8.297236114758786796L19",
  "0.38816355482824754693L0" },

{ "-2.7181316933272033506L-21", "-7.7081523870452907184L19",
  "0.20951773300223540615L0" },

{ "3.755562697893016061L-21", "-9.043255746258523336L19",
  "-0.33962513948155180184L0" },

{ "-6.788248742851763723L-21", "-2.3639021583849588926L19",
  "0.16046755854881268057L0" },

{ "-4.100847017987407598L-21", "-3.6481227061862975968L19",
  "0.14960393120916230025L0" },

{ "-2.001548479939126796L-21", "-8.705055796099425971L19",
  "0.17423591196468091344L0" },

{ "-3.670443367722997441L-21", "3.6588667206894740936L-22",
  "-1.34296630883370731296L-42" },

{ "-6.6783435670093499397L-22", "-8.113066551196750321L-21",
  "5.4181845810903550342L-42" },

{ "4.816859192586505112L-21", "-1.1868626619923445382L-22",
  "-5.716950323755514841L-43" },

{ "4.6402358755296483015L-21", "-4.244356902115351796L-22",
  "-1.9694817165747535215L-42" },

{ "9.3247068197076461794L-21", "3.5271238356611001996L-21",
  "3.288939568434245211L-41" },

{ "8.7860048755888267426L-21", "7.187872989134290154L-21",
  "6.315268712764710716L-41" },

};