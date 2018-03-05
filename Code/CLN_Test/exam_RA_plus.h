#include "mainheader.h"

static plus_test rational_plus_tests[] = {

{ "-6069217517368004039/4076344942716985944", "-399587800008780737/578697755310708616",
  "-321318766345655960630110128852941297/147435729263904928853096856396980844" },

{ "-41285036778370718/305793940074617155", "-1396094619926552183/15846027887642356854",
  "-1081121118676718273499338028514700537/4845619302294419132297197085940230370" },

{ "15975644088444536091/18063939613598316583", "17501188199168431305/2979264551795273683",
  "363736076920798535449296038324193823968/53817254956563877935003279344562385189" },

{ "10197734562406803221/17452826108659293487", "14639450560606090654/236781760961536951",
  "257914422508077920978698094723491089669/4132510899763835955061848877304138137" },

{ "-16810360766832230069/13652857552883800956", "5011749175730438558/4169057419710079215",
  "-184295743992738197672588473692806043/6324394120121667288243293659228081060" },

{ "2234573531734039025/1128831476977636536", "5842177084459535064/10255356071975483971",
  "29511180623959738330730559435115466579/11576568741659658592450950022331964456" },

{ "2268894928233321367/45672733521488298991909987382109984899", "-10510750087507287356/187832098427494353069556175466145198255",
  "-53883392376116199828369509984040539934420061636271022459/8578805378260910951788610598591490227836321974082207035230408675959411151245" },

{ "14273433611429514043/7774518083776389556784045601066955324", "17247074371340283485/225579726714102822702316919752160926694",
  "1676942472465190408518249346164012571239098147062478293991/876886832336064155131767120243155911448808491410701588797601053820468509428" },

{ "-384768590020206817/26284423885474502132625533495652664626", "-913687410374243983/254477371735734658619949996700223764026",
  "-10160887225658731404416073535892287983824191154410167550/557399258996959835387173465565070652935481894323496556880024318994528462023" },

{ "-4465222504572200650/89674568206322981678158378582739708537", "4148550863841320780/74302497820894496090312266744880513261",
  "2118016946376507498169590394563632549990739165791772590/350686547828419379316750498534703170285368675911953477374458878558215968903" },

{ "-4466938407638238142/281859125741189685767904931589784285893", "7302241525893379697/204618108204962312932373858463395271264",
  "1144186926000295881841982161759159994442430111060328362933/57673481089466829503954266461746705742702466399988738560842837126631263478752" },

{ "6692616266348342275/280491911593106290120490189988812804382", "5414100524539959087/183579771905991028181574615911067652873",
  "2747240373316006570071525025488180559154305534334705425309/51492641151737853299832848099101317109893853469394209716061486746077629289486" },

{ "-2794289802081124319/15768464977850217600859580216291365931410230647587457388598921425875331529149", "10869776169503285673/33805119742344157512165738805682358903614971418053290198565741206390317449856",
  "76938383491719886409504555688515759257937029058461512747558964579607347503639994773101488934213/533054846729186819415263583890627325668798847177803707144003483502948153457972377767011992167761176556555806720273883868208938866192358148729990609852544" },

{ "-253222140119290489/2123024034843473393742534167007121513293496410591072104903085284304117612082", "17957334013642389787/32058972871090153103034645121513493401113378486125580864856088310966601405847",
  "30005809992231287609744177955201962181880644831204431411802631067134766877061419104162728517351/68061969937719269465960475690278941280799593161143759512261685488134507341176789799765185182008442410081522124548392827986923668912612728349293792643454" },

{ "-13318881947309618/3105936147298438543619802738126617974207009907186580731552500517452462642139", "1850968757748704519/36469179946212878965111748233319050931475015876401494718861814560453153824935",
  "5263262069792987469108717688485565287648879759118200779949761992573778798556738644541735401311/113270944257273905484832818286307416845956086746130199501242465128236430928807948126409718436237517505516279133169796919230385184900609912160483959935965" },

{ "-9937822914683494298/36414156259035675966580098631253549474580108307284844243190992829476777586283", "-13712605099585970325/17758145954890657915358548152198427387923366136638180213650029984340849686198",
  "-675810254607579372158951115566887998278519717754376916387787672973408477396668549189167387350979/646647901672150721610792561233068038707362067627156669418022102308446036384411330678972562863413004325878365438890328206637571985169324874284800419222034" },

{ "2479135971595944301/28169711053558469409458629766960029324030958129245230797895768033968717159836", "3427244662960653095/28446538857424788738244844756675951434179713170118835630969510829753715142438",
  "83533664807147783700314944003289704497366290621039272787320536148072960487262393639109696219129/400665390043739792096386856839000624247597803909916773326187593475005945995926511155915226239317839405221783416485999405286913042389632370302962776360084" },

{ "14865500635281371370/56222262470894935247131881777606182311286871927285650835673424014252462156319", "6436092572090050725/19282524131572095520593158313261757267758159099923763177708581262473988426947",
  "648496060602737474174747620183913927791943082591316359990137585798909535115053578637078811588665/1084107132826611778585714784136700465449309125114745313342842325649687943726086785657821763235618936882528385000712567133180567926723616940173290425928093" },

{ "340196811925805824067049620503247332111/14422464039094716975", "51285507111580975533385007190438537498/3230944134273302873",
  "1838820276033673324738967436225477772648372110186756083453/46598175588880723338390245118389369175" },

{ "-210449319160504160992731982827917332322/5436857856220342451", "251628249079137248539965770847855056283/4323109210037952829",
  "458271632943884346915405609513071881239303671882386130695/23504130271893362375786510953364243879" },

{ "-40984360445255688839942109197081457275/6593417935076565019", "-138094174027187773198981391229349265879/7135512300754720691",
  "-1202957011856131413678873259651070808566709454882536663726/47047414779755620074837011989046108129" },

{ "-289704472880230079383856507128133962457/10452740760651010288", "-55251460678415911958671096669490155237/10333740726609314202",
  "-1785630052601050832889834016432677758176770083879794496285/54007956451514283340719766211063255088" },

{ "276702099951674677215621541062877777467/3899918017008359516", "42623843937285717338660228144403811741/1973785812353331893",
  "712380176058162142132059442064597996057720566915757732387/7697602851312240113570356856612843788" },

{ "-323480614013303716597188084301661616596/12957985934572321773", "-72966206939397711493108854138997499334/4539020357040680881",
  "-2413780175334213399707013296172687953960842714316410700258/58816561943270580900205343368941122013" },

{ "65443777543319569578713907336699651721/218804857459609839540825438673960136766", "-61986861924091374470669233802827103921/65997977315012279293170493460332070399",
  "-9243869541956614722377007489838492339200370508580665293676272508698701352807/14440678019033825487758061900150103876633207457375858942267120523885980189634" },

{ "75417845823236070411341994633288547531/70553457686181702397810927701121800017", "-7132208259849175775323757110664708879/24379326462014713478002790304943339422",
  "1335434330716260509518880689691257567128541829706203586134358870209350816139/1720045777955364955754847231620711706115121721983605654691934662747636370174" },

{ "-144692585186931942602350348772472248638/135233395864627580439431775527364081053", "282512666765911374279543408363363928190/317835040256607665191397469890906044457",
  "-7783226336195038987381961251409043080655184208289882004756343793157154115496/42981911818671667582796085276418080952868666330715445603855323471628969373221" },

{ "44888992584766727877549626240272070725/30583318432547259097085073976959329092", "8004917623696885952432014881247978821/22005016116109025986417835664774768346",
  "616299974987760892931461886440810919939264155149950328291076750435394215691/336493207496148335911511951044490614757807556827643881435283379298939260916" },

{ "78378756441281199312006031491361997668/175125578595003447448566412156266355477", "41128705932035853424044828385766740319/216359823601433445464965619660717081261",
  "24160702340946845080381231961736762955784254747832931999121777482667650876511/37890139292913914697800186893609983979783140570423836226844401085057321416497" },

{ "-36669293296367265584135816683983780855/7341750629088488427994322429098120058", "-110335983484012479290765295565662258281/5944410911181873015545360879141666465",
  "-1028036623331099574157832708037007047972965676333418398303213384036005227873/43642382546729990922161061763293407461832155878510163500678954788762454970" },

{ "228535455883892721240720366651075744967/13353170075841095813026701300679754576855418298534901819672803635370738730013", "50622643250826426975012800479360461693/18462345430382979738234695697296360785230118465695284267226773073149552698303",
  "4895273294635392498665165879164922265508724130843670837390305811645771221742112327485665544066552056189958877583010/246530838530831602270074647792752210668736478466245992891169449973883874207653264921203783108295835419855394180777469634862446033810927048792871560267939" },

{ "11355068601761731966774720678777239425/4604724775053993730579400400679579947095967462408565975449642189823843820753", "140083339434585694465706029861026468774/44667214322013486680993684507177513903616004462434123967566781106229226297333",
  "1152244506542792151980649054527153167035843960949499862764543674633978109831264344257976000890169981044543787620347/205680228421222079539939271800361418862113882206694593495620042859527547538342323521609420336002641308832164587573546802806916292021672743366881933951749" },

{ "-1347509007210283053816302848714698886/1127513773036247565111791991337919355855664936242166138889250311777351432819", "-29464928273311615445392112247506626497/61933028109313748081628643142485450090725737246358993405254280723087421657760",
  "-116677425670791909053501267317366054796703074907755330120413752187834449333299886015456661052906469074533366060403/69830342199092322009251417145364324484174202256910311362396720371574344280505889954115533896831727771442604285956749924105078563356474162416148250025440" },

{ "-324250487660721070279458563122233299722/81069650926979269606211148691445887485067008319429991878657612702576019034861", "221744296343315457943731256980089803078/69422237643162665956763790134527973903052044485041686255401689654420090859107",
  "-1511153903564243978242173323335554031611949546418082039382510246845821774680210236992700372319944685567533765722032/1876012190766999122356500320654631447623282613780323887424324139799202291067983209550065997185860196433399782230215269625922714982832188312141580824109709" },

{ "-5518324152042099343909980322067306333/114786626838714403445081775763480415805466836213320421844559660900880511042496", "-34415425451618992284220085078832944671/96012285963709194218263616278916829663708037691620330613749177799086889040577",
  "-121088040955051148243092870850103339772063863319219725752028251933576579890093496821887384992074112246777968211161/297862876779681729593084954525306275464788137269287692384941959703420459939692410434239827100068259769782676124741025632728203586961467995819025176090816" },

{ "-14763921690861243371082340598041267817/5580497386043551028888310256097864185640794395615400088682607872958152738111", "-37917865546640067592937379176813765341/6460563866107795917092814416816176677900242086501650458839130903088333290440",
  "-306983808565398982164654624310995401934900925070311336095043743767915008644459192438083753301097540174379867380331/36053159767181973313125557585868206969047484351694148822117591172786449966899079869470557965303954072842600790897257698854023751399649072014440219958840" },

{ "-50167218239107621378232529938205077788547946059832391744348095230748591585676/15685777859540025727", "2959973815535345735348053015389999235839609978295604181643547897863515739931/7556072538495923601",
  "-332637648328710384664787658442281566361265475773778265650094684540358159241317316408573560734439/118522875329417757148187346888166482927" },

{ "36275100136090483878026478935942224245036692059657264537598788566553406654319/7192442039871568876", "31833552596558882106090352174644817045294359487590746360517241517440556146007/5115621724114081523",
  "6795584791386081942310910570767193224876510928834120433155946649367201608618436115134135392229/603177258173744207443043238127434068" },

{ "1518304705177739493483387141342904186483658277690975456045607777812450680478/1837349761252804045", "-98159070764971437450169149833809835519268242923913777966502463698396945141091/17238232824535200528",
  "-154179655228376218743158291724235398278770272999447263973992852061897564252670941977524115620711/31672662964580000612902147746364535760" },

{ "-16820231344048323866426670709751443650129113909724546927974450301780935205864/4879137683452153951", "41987219452495799378686134495924115238909423831017150785452046648616005475639/10470103987572807938",
  "28751853386830083847297108941057082854166610198448421498169760256533906032780671559334244751257/51085078915429149801779227663330863038" },

{ "106981694162678522688926793970551228214793665448093395251834862896418045995969/12359470989873920972", "57736849967187961211538031441400807467468650239660040144967046985609433512403/9148121311784151716",
  "211534804819567028232303054650327703050869189253958355919997046592895748577556985792570078031065/14133242495605447754080611005730273494" },

{ "32477400086615533920132766925666506741908300936974348739732763951610256880146/9045135183308696243", "-27444990730472195954051975667481893116650518055101159075033425831129583042846/14815776448343565085",
  "232934248044934592851252865496377968609159820017147884670610366058217203617961573611006127074832/134010700820948737148715427669965475655" },

{ "-110053921687226074580746319073262192216481755737797790655164396095655530752161/255625377233605953547425802301922658850", "104095037267817888539158192425982072195078148060302393917025130946535913363779/52156238014583575190277280296975732513",
  "20869334635774913818120011435677143948904421430726712952150525645851498022294865158343391008006649321440592131083557/13332458017563665620865770931104425383051282278510599570476131200251352190050" },

{ "-29732769078100192507326444863945498799317005912797369958801703828462203585495/153426302667449722633466432797809987061", "36094569840376017510791155197897623093337784636438580042046806320700826250193/73286165979315961333009750429763545174",
  "3358855747298609357265422062476767573626163217619249414656940907348235709105513077913806378841119674678021275101643/11244025482879487592663298816607141776071841230792806495601092332558428993614" },

{ "-5942892427460131788264792587455286675871284855854073854440582948253436001319/42136930106315714728428443448730580823", "4013357443728612356640061171485791666303136232331145404661874650095235381569/4039594279673425548586623641599574814",
  "48367895947790658831309709091377784501687363167039737892874371817395083020674648576881857510385191335175551957207/56738700606823969419119152217721454504573192499839513549171731025354063974" },

{ "83833896550100013648317056712064289497247852876055488793078639582729685477353/188580876675619574786621140720273228537", "-94310653397371924313725082402708514144086936359594289802762093989853507835016/223423274286761439988276492107364036191",
  "945257965914081840217765265999453398105151083284254483307155736205796420255026737575918161700355729594975143830831/42133356934734885127066999419230498520039134905254787577957770920054881982567" },

{ "-14753992026457621496269953958381833108089826525439816493815533773338622353285/187171041855711408638339193132645929319", "41340837577662628944845446369855468662228665858415210386857356535970453143469/322471558852595372991189266479896691326",
  "993354944176102401496932276511264091214577507066786487301109889019709943488537161608732610457423116833164991120567/20119112546425211128699888199278894685207186285215928241217590790016852128998" },

{ "1370528773439579327226257222995383030603284075640526658282329726447335048230/305600505683287165495713194488435114383", "65450762047588146235054351616480175308174618406941901794570541085963681607527/78934496562987400429145916504112602768",
  "2234440886428442112499564751364146150136438855986167755259621093816030535881959724370423862435538502079424185584609/2680269118389404699570998335430047660909241475691839354273569734988880268016" },

{ "-76890617375308981455205142622328108690129081798840077873315966300000409208129/15716637731576156581128288257209679492686622162926707938907282962815471734862", "38716252217351070567267262306332875768795464072349655597599997486613800623507/8966639693620677733207403249675415446338239705879120765911896990394928596139",
  "-80961151400006413290662155450270992168701818633203071886556882897757813544592915596861717853520674107309124394292702460320442121704840951425284048212897/140925427734207212133604717335369986754855062343668899363006574618520848268718851310007161609443093589067206438198588881828988648068282656538084484897818" },

{ "-43290760758277846058307167265569849910514905939554272559141355223092464986939/39390771697068809730875092892395235497943839933482798653607450783947201796777", "-34021960935937170163894986285771504067448629886312440795733904794894095253649/106500928228745564800818258673435811176493306775154643113582742982704678574998",
  "-5950657500399238361998292872481533631424138885403498309639150240712482075115081624153513501886127772738596607451116548616099047843190357858736503567640395/4195153749384427435979718872073512266029328962522899010907363614544821318917440413166534226890289043064894115954085809567292470182917919104836361549181446" },

{ "17906146982204022925114071077515882010955693727109005464426577098738402001871/11978213712662686419384559301746021856683603106261241838035626618416021524231", "37108371752538653389309509075248119316034595087990649061240232817571629131708/23044877611981158676785639370406786635050056158699399001947422631523989139615",
  "857136973087880657664203854652754375000000796400911171478039451763440064550649429609696307332611304395324153178602635490321877797571177424460384122636213/276036469018466057777760709173569478463866562650149880633721199971933767458324034017734890892482223472007882939609440193626728031771767304374122564511065" },

{ "-77062185592993847534024832256462395143306675613123510837298699277378172890089/108133793614758275822883834459865239455798743725021300772336023406871185253111", "11169356025540464491224577661206910726665825152149521753528516637690366838655/6369000033300801574913390611244042297918207179453133439308688067382050608197",
  "716975776667538986425481530620118513423964367153518065425241139444161780269039780459555836804116752462325735011822817367819625929553250251515977390346172/688704135133337463423649074673019029541747166391680122270752018123634233590688096940261480888455237095078029621363428114402137147558304641222314936350867" },

{ "13583698920327742567560325715281067532806062839142769830536738488850089822247/37364394142255392010559408553278838878570049727027927213977555360874308098434", "89809462356450792524214360688853318641058652796345720882094866396911421360072/67457610947238032712889230619376608100793287037427539672885124981055281513463",
  "4272000026182362299819817378001862956001381379478285995446709640464951377212652125169846305230835604666564953883168949950485767679005929254184987140738609/2520512763327523955464432226120154092742373168521113224665257966793820057379494860454732800329019773731110452438496395974166220481124541266348389100216942" },

{ "-56124163112538495128545947597589743957824668875494126834084658670528264380488/4752969512023182700122983723156599300062332404522277372984645779569746369511", "-24794747728228571193100294011820993825205231022194400752319729320185378063197/98168688073468429337427023004226732413974455700654808087001957859427678524065",
  "-5627484141989830997868845457242226973925524393512774885292323552602180052845805156311097870316601631410500655735815037997645271136502511615781690896430387/466592781448509275992390948177487068548424631274164031114910250651063315574511979617153568070687706304645818907382693929886654490427484894987856595782215" },

};
