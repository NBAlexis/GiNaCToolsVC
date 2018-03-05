#include "mainheader.h"

static floor_test ffloat_floor_tests[] = {

{ "-0.8227301", "-0.25283414",
  "3", "-0.06422769" },

{ "-0.6686161", "0.4833234",
  "-2", "0.29803064" },

{ "-0.57436657", "0.52642506",
  "-2", "0.47848356" },

{ "0.60395426", "-0.61624163",
  "-1", "-0.012287392" },

{ "-0.21636301", "0.90365344",
  "-1", "0.68729043" },

{ "0.8705054", "-0.7953333",
  "-2", "-0.72016126" },

{ "0.4544462", "-9.890925E9",
  "-1", "-9.890925E9" },

{ "-0.4954149", "-3.8786918E9",
  "0", "-0.49541488" },

{ "-0.692049", "6.4791506E9",
  "-1", "6.4791506E9" },

{ "0.75464755", "-3.618496E9",
  "-1", "-3.618496E9" },

{ "-0.5929247", "-5.442471E9",
  "0", "-0.5929247" },

{ "-0.30383867", "9.262864E9",
  "-1", "9.262864E9" },

{ "0.9345329", "3.26737E-11",
  "28601991168", "0.0" },

{ "0.3772617", "-7.991702E-11",
  "-4720667648", "0.0" },

{ "0.74438447", "-1.0977978E-11",
  "-67807064064", "0.0" },

{ "-0.9220973", "-1.2655998E-11",
  "72858525696", "0.0" },

{ "-0.4615329", "6.48833E-11",
  "-7113276928", "0.0" },

{ "0.2851941", "-8.262349E-11",
  "-3451731456", "0.0" },

{ "0.61539984", "3.5826177E19",
  "0", "0.61539984" },

{ "-0.8195054", "8.793426E19",
  "-1", "8.793426E19" },

{ "-0.26412165", "7.015103E18",
  "-1", "7.015103E18" },

{ "-0.527393", "8.434833E19",
  "-1", "8.434833E19" },

{ "-0.1846056", "1.8252128E19",
  "-1", "1.8252128E19" },

{ "-0.6079822", "6.106683E19",
  "-1", "6.106683E19" },

{ "0.5564819", "5.953872E-21",
  "93465542827563810816", "0.0" },

{ "-0.52575815", "-1.8358678E-21",
  "286381261476583178240", "0.0" },

{ "-0.6321403", "-5.830945E-21",
  "108411292344853200896", "0.0" },

{ "-0.9675891", "-9.936226E-21",
  "97379936163841703936", "0.0" },

{ "-0.63503754", "-5.0137436E-21",
  "126659359065470140416", "0.0" },

{ "0.8053654", "-3.4055888E-22",
  "-2364834534832713236480", "0.0" },

{ "8.784645E9", "0.9775517",
  "8986374144", "0.0" },

{ "-9.314413E9", "-0.8318871",
  "11196726272", "0.0" },

{ "8.4695936E9", "-0.9823455",
  "-8621807616", "0.0" },

{ "-5.8406625E9", "-0.031723082",
  "184113971200", "0.0" },

{ "-7.325545E9", "0.93169844",
  "-7862571008", "0.0" },

{ "-5.2999526E9", "0.11515945",
  "-46022733824", "0.0" },

{ "6.680458E9", "7.170729E9",
  "0", "6.680458E9" },

{ "-2.2146278E9", "5.2909993E9",
  "-1", "3.0763715E9" },

{ "6.4947005E9", "3.1265188E9",
  "2", "2.4166298E8" },

{ "7.947109E9", "2.464481E9",
  "3", "5.53666E8" },

{ "8.899791E9", "3.5788132E9",
  "2", "1.7421644E9" },

{ "5.272568E9", "-5.3260964E9",
  "-1", "-5.3528532E7" },

{ "9.729838E8", "8.6379175E-11",
  "11264101901890748416", "0.0" },

{ "1.210882E9", "-4.412428E-11",
  "-27442532596777484288", "0.0" },

{ "9.169561E9", "-9.41537E-11",
  "-97389277614631288832", "0.0" },

{ "9.289745E9", "3.1269442E-11",
  "297087021478284623872", "0.0" },

{ "-5.334722E9", "2.0158666E-11",
  "-264636651022615314432", "0.0" },

{ "9.910798E9", "-2.985589E-11",
  "-331954558296456691712", "0.0" },

{ "-1.7169357E9", "2.220112E19",
  "-1", "2.220112E19" },

{ "4.9906683E9", "6.857979E19",
  "0", "4.9906683E9" },

{ "-9.90463E9", "-2.342953E19",
  "0", "-9.90463E9" },

{ "-5.4878054E8", "5.438576E19",
  "-1", "5.438576E19" },

{ "-6.1080986E9", "9.25119E19",
  "-1", "9.25119E19" },

{ "-8.4138286E9", "-9.682224E19",
  "0", "-8.4138286E9" },

{ "2.7084977E9", "2.542436E-23",
  "106531597407755826831748572905472", "0.0" },

{ "-5.720767E9", "9.438407E-21",
  "-606115738076318963177881600000", "0.0" },

{ "-3.4958034E9", "9.250327E-21",
  "-377911344579488968728001904640", "0.0" },

{ "-8.3702047E9", "6.0186186E-21",
  "-1390718493086361392338557730816", "0.0" },

{ "-7.517619E9", "-9.417701E-21",
  "798243593937800371539149848576", "0.0" },

{ "-2.1220838E9", "3.931208E-21",
  "-539804494597454582830132625408", "0.0" },

{ "-3.9606828E-11", "0.34267086",
  "-1", "0.34267086" },

{ "2.495503E-11", "-0.4518087",
  "-1", "-0.4518087" },

{ "-7.98698E-11", "-0.5665642",
  "0", "-7.98698E-11" },

{ "2.1465689E-11", "0.17276591",
  "0", "2.146569E-11" },

{ "4.9463066E-11", "-0.5659616",
  "-1", "-0.5659616" },

{ "-1.8961567E-11", "-0.7758364",
  "0", "-1.8961567E-11" },

{ "7.8871874E-11", "-5.768549E9",
  "-1", "-5.768549E9" },

{ "-9.079439E-11", "-3.807195E9",
  "0", "-9.079439E-11" },

{ "7.879919E-12", "-1.9198149E9",
  "-1", "-1.9198149E9" },

{ "4.389072E-11", "-8.657572E9",
  "-1", "-8.657572E9" },

{ "7.430157E-11", "-3.8599355E9",
  "-1", "-3.8599355E9" },

{ "-5.8839114E-11", "-5.3409536E9",
  "0", "-5.8839114E-11" },

{ "-3.3353615E-11", "8.9096924E-11",
  "-1", "5.574331E-11" },

{ "6.335122E-11", "3.606541E-11",
  "1", "2.7285809E-11" },

{ "-5.6885465E-11", "7.070333E-12",
  "-9", "6.7475353E-12" },

{ "-7.581576E-11", "-3.4334775E-11",
  "2", "-7.1462155E-12" },

{ "3.6686505E-11", "-1.9221425E-11",
  "-2", "-1.7563462E-12" },

{ "3.066395E-11", "-2.3198866E-11",
  "-2", "-1.573378E-11" },

{ "9.1089344E-11", "7.429058E19",
  "0", "9.1089344E-11" },

{ "-7.2265194E-11", "-6.5831596E19",
  "0", "-7.2265194E-11" },

{ "-4.9087675E-11", "1.9182038E19",
  "-1", "1.9182038E19" },

{ "-7.907188E-11", "4.405831E19",
  "-1", "4.405831E19" },

{ "6.118759E-11", "3.4342181E19",
  "0", "6.118759E-11" },

{ "5.4731882E-11", "-5.861447E19",
  "-1", "-5.861447E19" },

{ "6.121101E-11", "-1.8234462E-21",
  "-33568860160", "0.0" },

{ "9.788758E-11", "-2.65478E-21",
  "-36872200192", "0.0" },

{ "7.827001E-11", "-8.5754775E-21",
  "-9127189504", "0.0" },

{ "-3.738018E-11", "-7.810784E-21",
  "4785714176", "0.0" },

{ "7.31308E-11", "-2.0431058E-21",
  "-35793936384", "0.0" },

{ "9.4578095E-11", "-3.0466443E-21",
  "-31043366912", "0.0" },

{ "-4.8186137E19", "-0.95250696",
  "50588749896299315200", "0.0" },

{ "9.548003E18", "-0.9061317",
  "-10537102614582001664", "0.0" },

{ "5.5254813E19", "0.51959753",
  "106341562860634636288", "0.0" },

{ "-4.2787504E19", "0.14769173",
  "-289708190148186865664", "0.0" },

{ "-4.27109E17", "-0.03677529",
  "11614021477430460416", "0.0" },

{ "-3.9238043E19", "0.26663417",
  "-147160597790283792384", "0.0" },

{ "-2.0174873E19", "-6.7035556E7",
  "300957794304", "0.0" },

{ "1.6296811E19", "-7.2014956E9",
  "-2262976000", "0.0" },

{ "7.794499E19", "-7.412829E9",
  "-10514876416", "0.0" },

{ "-1.2546485E19", "6.1565005E9",
  "-2037924864", "0.0" },

{ "5.4549757E18", "-4.778849E9",
  "-1141483264", "0.0" },

{ "-8.9214324E18", "3.0002557E9",
  "-2973557248", "0.0" },

{ "8.790958E19", "-8.224902E-11",
  "-1068822197453670185020302557184", "0.0" },

{ "9.029222E18", "1.3127345E-11",
  "687817816164697187548814901248", "0.0" },

{ "6.7356843E19", "-9.1816894E-11",
  "-733599685837775742566290948096", "0.0" },

{ "4.0346153E19", "2.0593792E-11",
  "1959141510822234462049892564992", "0.0" },

{ "1.3402778E19", "-4.8733902E-11",
  "-275019611403690085233016700928", "0.0" },

{ "-1.3005549E19", "5.6579824E-11",
  "-229861963021783171398467846144", "0.0" },

{ "8.550302E19", "6.4624324E19",
  "1", "2.0878699E19" },

{ "4.7897585E19", "-1.5724218E19",
  "-4", "-1.4999288E19" },

{ "-8.6050445E19", "1.4007867E19",
  "-7", "1.2004627E19" },

{ "-6.0799387E19", "-5.667626E19",
  "1", "-4.1231221E18" },

{ "-7.847746E19", "-3.972193E19",
  "1", "-3.875553E19" },

{ "-6.425414E19", "3.0601436E19",
  "-3", "2.7550168E19" },

{ "2.8220074E-21", "-0.9401483",
  "-1", "-0.9401483" },

{ "9.867747E-21", "0.86288685",
  "0", "9.867747E-21" },

{ "6.2856053E-21", "-0.5235996",
  "-1", "-0.5235996" },

{ "8.709991E-22", "0.42678982",
  "0", "8.709991E-22" },

{ "1.0493481E-21", "0.9355661",
  "0", "1.0493481E-21" },

{ "-6.137466E-21", "0.4328317",
  "-1", "0.4328317" },

{ "6.5872774E-21", "-8.80464E9",
  "-1", "-8.80464E9" },

{ "-1.0479629E-22", "-9.353607E9",
  "0", "-1.0479629E-22" },

{ "-2.636932E-21", "9.794678E9",
  "-1", "9.794678E9" },

{ "-7.912024E-21", "-2.9102356E9",
  "0", "-7.912024E-21" },

{ "1.0071349E-21", "8.762459E9",
  "0", "1.0071349E-21" },

{ "-6.795979E-21", "-9.445545E9",
  "0", "-6.795979E-21" },

{ "6.0598967E-22", "-3.961637E-11",
  "-1", "-3.961637E-11" },

{ "3.481348E-21", "-7.485006E-11",
  "-1", "-7.485006E-11" },

{ "-5.610974E-21", "-4.073898E-11",
  "0", "-5.610974E-21" },

{ "-6.2362584E-21", "8.403202E-11",
  "-1", "8.403202E-11" },

{ "4.2029927E-21", "7.823452E-11",
  "0", "4.2029927E-21" },

{ "-7.765272E-21", "-8.502908E-11",
  "0", "-7.765272E-21" },

{ "2.7845436E-21", "3.490416E-21",
  "0", "2.7845436E-21" },

{ "-1.4630091E-21", "9.193901E-21",
  "-1", "7.730892E-21" },

{ "-8.1823826E-21", "8.941324E-21",
  "-1", "7.5894165E-22" },

{ "-1.8218875E-21", "3.8057304E-21",
  "-1", "1.9838427E-21" },

{ "5.8037763E-21", "-5.1721612E-21",
  "-2", "-4.5405462E-21" },

{ "-8.179982E-21", "6.2204556E-21",
  "-2", "4.2609293E-21" },

};
