Configuration:
    P4 2.2GHZ / i850E / 1GB RDRAM
    Linux 2.4.21pre3 / glibc 2.3.1 / gcc 3.2.1, 2.96 
    Libraries as described in README


******************** Parsing Benchmarks ********************

--->Running <expat> benchmarks:
-> xmlgen 4 KB
Initialisation time 0.787 + 0.112(6.08%) ms, Parsing Time 0.103(6.60%) ms
-> xmlgen 256 KB
Initialisation time 0.033 + 4.049(6.23%) ms, Parsing Time 7.184(3.51%) ms
-> xmlgen 32 MB
Initialisation time 0.044 + 421.967(0.84%) ms, Parsing Time 898.700(0.39%) ms
-> opcgen 50 ( 3.5KB )
Parsing Time 8804.886000 ms for 80000 messages
-> opcgen 50000 ( 3 MB )
Parsing Time 7563.019000 ms for 100 messages
-> dmoz rdf file ( 12 MB )
Initialisation time 0.036 + 44.623(5.06%) ms, Parsing Time 271.972(0.83%) ms

--->Running <expat-arabica-dom> benchmarks:
-> xmlgen 4 KB
./runbench.2: line 27:   658 Aborted                 ./$name `expr $time "*" 85000` xmlgen 4096
-> xmlgen 256 KB
./runbench.2: line 27:   660 Aborted                 ./$name `expr $time "*" 1000` xmlgen 262144
-> xmlgen 32 MB
./runbench.2: line 27:   662 Aborted                 ./$name `expr $time "*" 8` xmlgen 32000000
-> opcgen 50 ( 3.5KB )
./runbench.2: line 27:   664 Aborted                 ./$name `expr $time "*" 80000` opcgen 50
-> opcgen 50000 ( 3 MB )
./runbench.2: line 27:   666 Aborted                 ./$name `expr $time "*" 100` opcgen 50000
-> dmoz rdf file ( 12 MB )
./runbench.2: line 27:   668 Aborted                 ./$name `expr $time "*" 25` ../xml.files/test.rdf

--->Running <expat-arabica-sax> benchmarks:
-> xmlgen 4 KB
Initialisation time 0.006 + 0.344(7.75%) ms, Parsing Time 2.373(1.12%) ms
-> xmlgen 256 KB
Initialisation time 0.007 + 0.316(191.54%) ms, Parsing Time 164.032(0.37%) ms
-> xmlgen 32 MB
Initialisation time 0.012 + 0.000(0.00%) ms, Parsing Time 19962.660(0.15%) ms
-> opcgen 50 ( 3.5KB )
Parsing Time 134387.182000 ms for 80000 messages
-> opcgen 50000 ( 3 MB )
Parsing Time 103602.384000 ms for 100 messages
-> dmoz rdf file ( 12 MB )
Initialisation time 0.008 + 0.000(0.00%) ms, Parsing Time 2504.761(0.76%) ms

--->Running <expat-cslxml-dom> benchmarks:
-> xmlgen 4 KB
Initialisation time 0.015 + 1.356(1.41%) ms, Parsing Time 1.361(1.41%) ms
-> xmlgen 256 KB
Initialisation time 0.020 + 0.600(87.44%) ms, Parsing Time 96.208(0.55%) ms
-> xmlgen 32 MB
Initialisation time 0.028 + 0.000(0.00%) ms, Parsing Time 11901.847(0.40%) ms
-> opcgen 50 ( 3.5KB )
Parsing Time 126052.290000 ms for 80000 messages
-> opcgen 50000 ( 3 MB )
Parsing Time 110241.003000 ms for 100 messages
-> dmoz rdf file ( 12 MB )
Initialisation time 0.026 + 0.000(0.00%) ms, Parsing Time 2421.706(0.27%) ms

--->Running <expat-cslxml-sax> benchmarks:
-> xmlgen 4 KB
Initialisation time 0.004 + 1.077(1.14%) ms, Parsing Time 0.406(3.03%) ms
-> xmlgen 256 KB
Initialisation time 0.004 + 0.264(154.33%) ms, Parsing Time 27.734(1.47%) ms
-> xmlgen 32 MB
Initialisation time 0.008 + 12.635(238.65%) ms, Parsing Time 3392.233(0.89%) ms
-> opcgen 50 ( 3.5KB )
Parsing Time 52372.044000 ms for 80000 messages
-> opcgen 50000 ( 3 MB )
Parsing Time 48079.993000 ms for 100 messages
-> dmoz rdf file ( 12 MB )
Initialisation time 0.008 + 0.000(0.00%) ms, Parsing Time 1011.862(0.12%) ms

--->Running <expat-sablotron-dom> benchmarks:
-> xmlgen 4 KB
Initialisation time 12.084 + 6.194(0.30%) ms, Parsing Time 1.139(1.62%) ms
-> xmlgen 256 KB
Initialisation time 0.105 + 1.660(25.92%) ms, Parsing Time 90.823(0.47%) ms
-> xmlgen 32 MB
Initialisation time 0.140 + 159.039(15.27%) ms, Parsing Time 11196.326(0.22%) ms
-> opcgen 50 ( 3.5KB )
Parsing Time 80900.531000 ms for 80000 messages
-> opcgen 50000 ( 3 MB )
./runbench.2: line 27:   714 Segmentation fault      ./$name `expr $time "*" 100` opcgen 50000
-> dmoz rdf file ( 12 MB )
Initialisation time 0.120 + 2.140(514.00%) ms, Parsing Time 2108.661(0.52%) ms

--->Running <libxml> benchmarks:
-> xmlgen 4 KB
Initialisation time 18.295 + 1.354(0.82%) ms, Parsing Time 0.323(3.44%) ms
-> xmlgen 256 KB
Initialisation time 0.143 + 0.000(0.00%) ms, Parsing Time 27.657(2.13%) ms
-> xmlgen 32 MB
Initialisation time 0.175 + 0.000(0.00%) ms, Parsing Time 3676.544(1.59%) ms
-> opcgen 50 ( 3.5KB )
Parsing Time 24706.714000 ms for 80000 messages
-> opcgen 50000 ( 3 MB )
Parsing Time 29416.727000 ms for 100 messages
-> dmoz rdf file ( 12 MB )
Initialisation time 0.164 + 0.000(0.00%) ms, Parsing Time 1056.735(2.55%) ms

--->Running <libxml-dom> benchmarks:
-> xmlgen 4 KB
Initialisation time 1.170 + 0.823(1.41%) ms, Parsing Time 0.341(3.41%) ms
-> xmlgen 256 KB
Initialisation time 0.023 + 0.000(0.00%) ms, Parsing Time 27.819(2.32%) ms
-> xmlgen 32 MB
Initialisation time 0.036 + 0.000(0.00%) ms, Parsing Time 3509.306(1.62%) ms
-> opcgen 50 ( 3.5KB )
Parsing Time 28450.469000 ms for 80000 messages
-> opcgen 50000 ( 3 MB )
Parsing Time 26758.503000 ms for 100 messages
-> dmoz rdf file ( 12 MB )
Initialisation time 0.034 + 0.000(0.00%) ms, Parsing Time 1048.987(1.74%) ms

--->Running <libxml-sax> benchmarks:
-> xmlgen 4 KB
Initialisation time 0.001 + 0.257(2.83%) ms, Parsing Time 0.133(5.48%) ms
-> xmlgen 256 KB
Initialisation time 0.001 + 0.000(0.00%) ms, Parsing Time 9.168(3.89%) ms
-> xmlgen 32 MB
Initialisation time 0.002 + 2.986(166.07%) ms, Parsing Time 1068.831(0.46%) ms
-> opcgen 50 ( 3.5KB )
Parsing Time 8691.185000 ms for 80000 messages
-> opcgen 50000 ( 3 MB )
Parsing Time 7160.274000 ms for 100 messages
-> dmoz rdf file ( 12 MB )
Initialisation time 0.002 + 6.737(50.04%) ms, Parsing Time 409.295(0.82%) ms

--->Running <oracle-dom> benchmarks:
-> xmlgen 4 KB
Initialisation time 1.673 + 0.165(6.01%) ms, Parsing Time 0.199(4.97%) ms
-> xmlgen 256 KB
Initialisation time 1.687 + 2.779(12.77%) ms, Parsing Time 13.247(2.68%) ms
-> xmlgen 32 MB
Initialisation time 1.757 + 255.554(23.99%) ms, Parsing Time 1685.128(3.64%) ms
-> opcgen 50 ( 3.5KB )
Parsing Time 54009.514000 ms for 80000 messages
-> opcgen 50000 ( 3 MB )
Parsing Time 47807.435000 ms for 100 messages
-> dmoz rdf file ( 12 MB )
Initialisation time 1.762 + 130.747(6.51%) ms, Parsing Time 2549.144(0.33%) ms

--->Running <oracle-dom++> benchmarks:
-> xmlgen 4 KB
Initialisation time 47.328 + 1.348(0.75%) ms, Parsing Time 0.204(4.93%) ms
-> xmlgen 256 KB
Initialisation time 1.728 + 2.684(12.93%) ms, Parsing Time 13.293(2.61%) ms
-> xmlgen 32 MB
Initialisation time 1.796 + 230.245(16.72%) ms, Parsing Time 1675.562(2.30%) ms
-> opcgen 50 ( 3.5KB )
Parsing Time 56404.723000 ms for 80000 messages
-> opcgen 50000 ( 3 MB )
Parsing Time 48144.496000 ms for 100 messages
-> dmoz rdf file ( 12 MB )
Initialisation time 1.808 + 100.274(7.38%) ms, Parsing Time 2603.064(0.28%) ms

--->Running <oracle-sax> benchmarks:
-> xmlgen 4 KB
Initialisation time 33.526 + 1.712(0.63%) ms, Parsing Time 0.268(4.06%) ms
-> xmlgen 256 KB
Initialisation time 1.676 + 0.207(184.47%) ms, Parsing Time 14.321(2.67%) ms
-> xmlgen 32 MB
Initialisation time 1.765 + 31.795(133.41%) ms, Parsing Time 1732.999(2.45%) ms
-> opcgen 50 ( 3.5KB )
Parsing Time 62023.589000 ms for 80000 messages
-> opcgen 50000 ( 3 MB )
Parsing Time 56625.213000 ms for 100 messages
-> dmoz rdf file ( 12 MB )
Initialisation time 1.745 + 79.737(15.54%) ms, Parsing Time 2732.307(0.45%) ms

--->Running <oracle-sax++> benchmarks:
-> xmlgen 4 KB
Initialisation time 40.306 + 6.783(0.17%) ms, Parsing Time 0.270(4.36%) ms
-> xmlgen 256 KB
Initialisation time 1.728 + 1.133(34.44%) ms, Parsing Time 14.365(2.72%) ms
-> xmlgen 32 MB
Initialisation time 1.800 + 8.720(403.52%) ms, Parsing Time 1754.337(2.01%) ms
-> opcgen 50 ( 3.5KB )
Parsing Time 65321.034000 ms for 80000 messages
-> opcgen 50000 ( 3 MB )
Parsing Time 49798.016000 ms for 100 messages
-> dmoz rdf file ( 12 MB )
Initialisation time 1.761 + 71.527(18.64%) ms, Parsing Time 2590.441(0.51%) ms

--->Running <oracle_dom2> benchmarks:
-> xmlgen 4 KB
Initialisation time 161.0 + 106.05877647058824(1.5646148880245383%) ms
Parsing Time 0.9412235294117647(176.30364678118173%)
-> xmlgen 256 KB
Initialisation time 167.0 + 290.923(18.596133587363802%) ms
Parsing Time 78.077(69.2911225026146%)
-> xmlgen 32 MB
Exception in thread "main" java.lang.OutOfMemoryError
-> opcgen 50 ( 3.5KB )
Parsing Time 74895.0 ms for 80000 messages
-> opcgen 50000 ( 3 MB )
Exception in thread "main" java.lang.OutOfMemoryError
-> dmoz rdf file ( 12 MB )
Initialisation time 161.0 + 874.2(6.1675362922482595%) ms
Parsing Time 1794.8(3.0040451452437202%)

--->Running <oracle_sax2> benchmarks:
-> xmlgen 4 KB
Initialisation time 160.0 + 73.37963529411765(2.417015947097543%) ms
Parsing Time 0.6203647058823529(285.89593672293614%)
-> xmlgen 256 KB
Initialisation time 164.0 + 140.457(3.5438341787096364%) ms
Parsing Time 22.543(22.08030507204096%)
-> xmlgen 32 MB
Initialisation time 162.0 + 272.625(50.37554558913519%) ms
Parsing Time 2679.375(5.125685324464841%)
-> opcgen 50 ( 3.5KB )
Parsing Time 42511.0 ms for 80000 messages
-> opcgen 50000 ( 3 MB )
Parsing Time 18804.0 ms for 100 messages
-> dmoz rdf file ( 12 MB )
Initialisation time 161.0 + 187.08000000000004(12.008395652092036%) ms
Parsing Time 981.92(2.2878958149272637%)

--->Running <qt-dom> benchmarks:
-> xmlgen 4 KB
Initialisation time 0.009 + 82.498(0.04%) ms, Parsing Time 3.956(0.85%) ms
-> xmlgen 256 KB
Initialisation time 0.010 + 0.000(0.00%) ms, Parsing Time 273.779(0.20%) ms
-> xmlgen 32 MB
Initialisation time 0.015 + 0.000(0.00%) ms, Parsing Time 33524.550(0.16%) ms
-> opcgen 50 ( 3.5KB )
Parsing Time 262572.176000 ms for 80000 messages
-> opcgen 50000 ( 3 MB )
Parsing Time 217514.224000 ms for 100 messages
-> dmoz rdf file ( 12 MB )
Initialisation time 0.015 + 5.579(296.62%) ms, Parsing Time 6651.952(0.25%) ms

--->Running <qt-sax> benchmarks:
-> xmlgen 4 KB
Initialisation time 0.174 + 2.026(1.81%) ms, Parsing Time 4.717(0.78%) ms
-> xmlgen 256 KB
Initialisation time 0.195 + 2.364(27.67%) ms, Parsing Time 326.221(0.20%) ms
-> xmlgen 32 MB
Initialisation time 0.239 + 0.000(0.00%) ms, Parsing Time 40126.055(0.15%) ms
-> opcgen 50 ( 3.5KB )
Parsing Time 285622.217000 ms for 80000 messages
-> opcgen 50000 ( 3 MB )
Parsing Time 232429.343000 ms for 100 messages
-> dmoz rdf file ( 12 MB )
Initialisation time 0.208 + 1.287(870.24%) ms, Parsing Time 7295.117(0.15%) ms

--->Running <rxp> benchmarks:
-> xmlgen 4 KB
Initialisation time 2.295 + 0.107(12.09%) ms, Parsing Time 0.409(3.17%) ms
-> xmlgen 256 KB
Initialisation time 0.550 + 0.000(0.00%) ms, Parsing Time 35.893(1.17%) ms
-> xmlgen 32 MB
Initialisation time 0.576 + 0.000(0.00%) ms, Parsing Time 4998.693(0.35%) ms
-> opcgen 50 ( 3.5KB )
Parsing Time 22670.324000 ms for 80000 messages
-> opcgen 50000 ( 3 MB )
Parsing Time 24481.213000 ms for 100 messages
-> dmoz rdf file ( 12 MB )
Initialisation time 0.522 + 0.000(0.00%) ms, Parsing Time 1017.108(0.33%) ms

--->Running <sun_dom2> benchmarks:
-> xmlgen 4 KB
Initialisation time 69.0 + 114.39075294117647(17.383317198502557%) ms
Parsing Time 2.6092470588235295(762.0936991104977%)
-> xmlgen 256 KB
Initialisation time 72.0 + 310.382(38.57449815609446%) ms
Parsing Time 65.618(182.46258475852528%)
-> xmlgen 32 MB
Exception in thread "main" java.lang.OutOfMemoryError
-> opcgen 50 ( 3.5KB )
Parsing Time 184300.0 ms for 80000 messages
-> opcgen 50000 ( 3 MB )
Exception in thread "main" java.lang.OutOfMemoryError
-> dmoz rdf file ( 12 MB )
Initialisation time 70.0 + 470.55999999999995(62.52104179580742%) ms
Parsing Time 1944.44(15.130269603297162%)

--->Running <sun_sax2> benchmarks:
-> xmlgen 4 KB
Initialisation time 70.0 + 101.35734117647058(1.8885808692759947%) ms
Parsing Time 0.6426588235294117(297.8587214523817%)
-> xmlgen 256 KB
Initialisation time 72.0 + 203.039(2.9821429019990866%) ms
Parsing Time 25.961(23.323112078848755%)
-> xmlgen 32 MB
Initialisation time 71.0 + 287.875(37.360624497320195%) ms
Parsing Time 3086.125(3.4850143066680874%)
-> opcgen 50 ( 3.5KB )
Parsing Time 53679.0 ms for 80000 messages
-> opcgen 50000 ( 3 MB )
Parsing Time 28827.0 ms for 100 messages
-> dmoz rdf file ( 12 MB )
Initialisation time 71.0 + 277.52(72.1275148476768%) ms
Parsing Time 982.48(20.373776484536343%)

--->Running <xerces-dom> benchmarks:
-> xmlgen 4 KB
Initialisation time 0.932 + 46.446(0.04%) ms, Parsing Time 0.942(1.83%) ms
-> xmlgen 256 KB
Initialisation time 0.163 + 1.389(20.67%) ms, Parsing Time 57.324(0.50%) ms
-> xmlgen 32 MB
Initialisation time 0.200 + 31.448(67.54%) ms, Parsing Time 7003.335(0.30%) ms
-> opcgen 50 ( 3.5KB )
Parsing Time 79980.330000 ms for 80000 messages
-> opcgen 50000 ( 3 MB )
Parsing Time 58727.436000 ms for 100 messages
-> dmoz rdf file ( 12 MB )
Initialisation time 0.188 + 5.250(61.58%) ms, Parsing Time 1950.283(0.17%) ms

--->Running <xerces-sax> benchmarks:
-> xmlgen 4 KB
Initialisation time 0.389 + 0.543(2.38%) ms, Parsing Time 0.475(2.72%) ms
-> xmlgen 256 KB
Initialisation time 0.418 + 0.704(91.62%) ms, Parsing Time 23.396(2.76%) ms
-> xmlgen 32 MB
Initialisation time 0.478 + 13.939(121.53%) ms, Parsing Time 2795.375(0.61%) ms
-> opcgen 50 ( 3.5KB )
Parsing Time 36053.482000 ms for 80000 messages
-> opcgen 50000 ( 3 MB )
Parsing Time 29520.794000 ms for 100 messages
-> dmoz rdf file ( 12 MB )
Initialisation time 0.467 + 3.310(115.50%) ms, Parsing Time 975.506(0.39%) ms

--->Running <xml4c-dom> benchmarks:
-> xmlgen 4 KB
Initialisation time 0.155 + 1.136(1.43%) ms, Parsing Time 0.939(1.73%) ms
-> xmlgen 256 KB
Initialisation time 0.161 + 1.165(25.13%) ms, Parsing Time 57.506(0.51%) ms
-> xmlgen 32 MB
Initialisation time 0.197 + 7.044(514.44%) ms, Parsing Time 6978.814(0.52%) ms
-> opcgen 50 ( 3.5KB )
Parsing Time 79947.483000 ms for 80000 messages
-> opcgen 50000 ( 3 MB )
Parsing Time 58714.133000 ms for 100 messages
-> dmoz rdf file ( 12 MB )
Initialisation time 0.187 + 7.984(11.85%) ms, Parsing Time 1941.317(0.05%) ms

--->Running <xml4c-sax> benchmarks:
-> xmlgen 4 KB
Initialisation time 0.395 + 0.548(2.33%) ms, Parsing Time 0.474(2.69%) ms
-> xmlgen 256 KB
Initialisation time 0.421 + 1.017(44.94%) ms, Parsing Time 23.215(1.97%) ms
-> xmlgen 32 MB
Initialisation time 0.479 + 17.348(73.64%) ms, Parsing Time 2796.146(0.46%) ms
-> opcgen 50 ( 3.5KB )
Parsing Time 36038.779000 ms for 80000 messages
-> opcgen 50000 ( 3 MB )
Parsing Time 29532.663000 ms for 100 messages
-> dmoz rdf file ( 12 MB )
Initialisation time 0.467 + 5.059(99.34%) ms, Parsing Time 975.458(0.52%) ms


******************** DOM Tree Build Benchmarks ********************

--->Running <expat-cslxml-dom> benchmarks:
-> 5KB file (20)
Building DOM tree in 3.417(0.81) ms!
-> 500KB file (2500)
Building DOM tree in 426.058(1.07) ms!
-> 9MB file (50000)
Building DOM tree in 19273.268(0.14) ms!

--->Running <expat-sablotron-dom> benchmarks:
-> 5KB file (20)
Building DOM tree in 3.075(0.89) ms!
-> 500KB file (2500)
Building DOM tree in 313.294(0.25) ms!
-> 9MB file (50000)
Building DOM tree in 9556.755(0.23) ms!

--->Running <libxml> benchmarks:
-> 5KB file (20)
Building DOM tree in 0.571(1.87) ms!
-> 500KB file (2500)
Building DOM tree in 74.352(1.20) ms!
-> 9MB file (50000)
Building DOM tree in 1494.444(0.46) ms!

--->Running <libxml-dom> benchmarks:
-> 5KB file (20)
Building DOM tree in 6.163(0.51) ms!
-> 500KB file (2500)
Building DOM tree in 667.003(0.59) ms!
-> 9MB file (50000)
Building DOM tree in 13378.890(0.13) ms!

--->Running <oracle-dom> benchmarks:
-> 5KB file (20)
Building DOM tree in 0.473(2.66) ms!
-> 500KB file (2500)
Building DOM tree in 19.687(3.12) ms!
-> 9MB file (50000)
Building DOM tree in 368.529(2.75) ms!

--->Running <oracle-dom++> benchmarks:
-> 5KB file (20)
Building DOM tree in 0.457(2.53) ms!
-> 500KB file (2500)
Building DOM tree in 17.897(4.14) ms!
-> 9MB file (50000)
Building DOM tree in 345.545(3.07) ms!

--->Running <oracle_dom2> benchmarks:
-> 5KB file (20)
Creating DOM Tre Time 1.4121132075471698(111.80482984317847%) ms
-> 500KB file (2500)
Creating DOM Tre Time 220.50833333333333(9.239588613103747%) ms
-> 9MB file (50000)
Exception in thread "main" java.lang.OutOfMemoryError

--->Running <qt-dom> benchmarks:
-> 5KB file (20)
Building DOM tree in 2.490(0.98) ms!
-> 500KB file (2500)
Building DOM tree in 253.285(0.36) ms!
-> 9MB file (50000)
Building DOM tree in 5168.907(0.33) ms!

--->Running <sun_dom2> benchmarks:
-> 5KB file (20)
Creating DOM Tre Time 1.4811698113207548(793.2420414550169%) ms
-> 500KB file (2500)
Creating DOM Tre Time 151.59722222222223(9.045461076906246%) ms
-> 9MB file (50000)
Exception in thread "main" java.lang.OutOfMemoryError

--->Running <xerces-dom> benchmarks:
-> 5KB file (20)
Building DOM tree in 1.805(1.10) ms!
-> 500KB file (2500)
Building DOM tree in 177.583(0.41) ms!
-> 9MB file (50000)
Building DOM tree in 3542.633(0.19) ms!

--->Running <xml4c-dom> benchmarks:
-> 5KB file (20)
Building DOM tree in 1.805(1.09) ms!
-> 500KB file (2500)
Building DOM tree in 177.651(0.37) ms!
-> 9MB file (50000)
Building DOM tree in 3542.984(0.19) ms!

******************** Schema Validating Benchmarks ********************

--->Running <libxml> benchmarks:
-> xmlgen 4 KB
Element data content check failed
Error in XML file!
-> xmlgen 256 KB
Element data content check failed
Error in XML file!
-> opcgen 50 ( 3.5KB )
Attribute MoreElements on BrowseResponse is unknown
Error in XML file!
-> opcgen 50000 ( 3 MB ) - 4 times longer
Attribute MoreElements on BrowseResponse is unknown
Error in XML file!


--->Running <oracle-dom> benchmarks:
-> xmlgen 4 KB
Initialisation time 19.880 + 0.049(30.73%) ms, Validation Time 0.061(24.24%) ms
-> xmlgen 256 KB
Initialisation time 1.573 + 0.026(1860.67%) ms, Validation Time 6.840(7.06%) ms
-> opcgen 50 ( 3.5KB )
Can't open XML file!
-> opcgen 50000 ( 3 MB ) - 4 times longer
Can't open XML file!

--->Running <sun_dom2> benchmarks:
-> xmlgen 4 KB
Initialisation time 6.0 + 143.2552808988764(14.35028770631174%) ms
Parsing Time 4.6293258426966295(1152.065931610222%)
-> xmlgen 256 KB
Initialisation time 6.0 + 307.57894736842104(36.34364567356568%) ms
Parsing Time 153.940350877193(157.5351546520942%)
-> opcgen 50 ( 3.5KB )
Parsing Time 35754.0 ms for 1600 messages
-> opcgen 50000 ( 3 MB ) - 4 times longer
Exception in thread "main" java.lang.OutOfMemoryError

--->Running <xerces-dom> benchmarks:
-> xmlgen 4 KB
Initialisation time 0.001 + 93.589(0.09%) ms, Validation Time 3.330(3.94%) ms
-> xmlgen 256 KB
Initialisation time 0.001 + 2.837(38.42%) ms, Validation Time 94.726(1.70%) ms
-> opcgen 50 ( 3.5KB )
Validating Time 25695.041000 ms for 1600 messages
-> opcgen 50000 ( 3 MB ) - 4 times longer
Validating Time 104771.399000 ms for 100 messages

--->Running <xml4c-dom> benchmarks:
-> xmlgen 4 KB
Initialisation time 0.001 + 2.794(3.12%) ms, Validation Time 3.327(4.11%) ms
-> xmlgen 256 KB
Initialisation time 0.001 + 3.506(24.33%) ms, Validation Time 94.317(1.36%) ms
-> opcgen 50 ( 3.5KB )
Validating Time 25816.201000 ms for 1600 messages
-> opcgen 50000 ( 3 MB ) - 4 times longer
Validating Time 104823.975000 ms for 100 messages


********** Security (Signature/Encryption)  Benchmarks *************

--->Running <libxml> benchmarks:
-> xmlgen 4 KB
Initialisation time 160.813 + 13.502(1.76%) ms
Signing/Verifying Time 2.889(3.20%) ms
Encrypting/Decrypting Time 3.840(3.80%) ms
-> xmlgen 256 KB
Initialisation time 5.196 + 0.000(0.00%) ms
Signing/Verifying Time 100.199(3.42%) ms
Encrypting/Decrypting Time 195.902(5.04%) ms
-> opcgen 50 ( 3.5KB )
Signing/Verifying Time 13927.135000 ms for 5300 messages
Encrypting/Decrypting Time 19545.772000 ms for 5300 messages
-> opcgen 50000 ( 3 MB ) - 4 times longer
Signing/Verifying Time 73811.959000 ms for 100 messages
Encrypting/Decrypting Time 155880.185000 ms for 100 messages
-> dmoz rdf file ( 12 MB ) - 4 times longer
Initialisation time 5.211 + 52.423(101.78%) ms
Signing/Verifying Time 1951.816(0.94%) ms
Encrypting/Decrypting Time 7198.033(0.49%) ms

--->Running <sun_dom2> benchmarks:
-> xmlgen 4 KB
Initialisation Time: 1073.0 + 815.5071111111112(15.309913671427303%) ms
Signing/Verifying Time: 633.4877777777778(19.675120498912545%)
Encryption/Decryption Time: 0.005111111111111111(4185.999230884459%)
-> xmlgen 256 KB
Exception in thread "main" java.lang.OutOfMemoryError
-> opcgen 50 ( 3.5KB )
Signing/Verifiying Time: 1691546.0 ms for 5300 messages
Encryption/Decryption Time: 13.0 ms for 5300 messages
-> opcgen 50000 ( 3 MB ) - 4 times longer
Exception in thread "main" java.lang.OutOfMemoryError
-> dmoz rdf file ( 12 MB ) - 4 times longer
Exception in thread "main" java.lang.OutOfMemoryError


************* XSL Transformation Benchmarks ****************

--->Running <oracle-dom> benchmarks:
-> xmlgen 4 KB
Initialisation time 1.143 + 0.314(26.19%) ms
XSL Transformation Time 5.913(1.39%) ms
-> xmlgen 256 KB
Initialisation time 1.316 + 1.582(83.50%) ms
XSL Transformation Time 204.398(0.65%) ms
-> xmlgen 4 MB
Initialisation time 1.351 + 0.000(0.00%) ms
XSL Transformation Time 3172.302(0.43%) ms

--->Running <expat-sablotron-dom> benchmarks:
-> xmlgen 4 KB
Initialisation time 1.852 + 0.295(48.98%) ms
XSL Transformation Time 11.373(1.27%) ms
-> xmlgen 256 KB
Initialisation time 1.888 + 4.488(48.67%) ms
XSL Transformation Time 543.755(0.40%) ms
-> xmlgen 4 MB
Initialisation time 1.948 + 135.555(25.14%) ms
XSL Transformation Time 8954.311(0.38%) ms

--->Running <libxml> benchmarks:
-> xmlgen 4 KB
Initialisation time 15.775 + 0.275(22.67%) ms
XSL Transformation Time 1.862(3.35%) ms
-> xmlgen 256 KB
Initialisation time 0.808 + 1.186(92.99%) ms
XSL Transformation Time 85.196(1.29%) ms
-> xmlgen 4 MB
Initialisation time 0.810 + 2.722(321.69%) ms
XSL Transformation Time 1337.616(0.65%) ms

--->Running <sun_dom2> benchmarks:
-> xmlgen 4 KB
Initialisation time 438.0 + 193.9606(15.876803777235782%) ms
XSL Transformation Time 7.0394(437.46262276826417%)
-> xmlgen 256 KB
Initialisation time 279.0 + 659.3(28.985836881667606%) ms
XSL Transformation Time 316.7(60.34216058125498%)
-> xmlgen 4 MB
Exception in thread "main" java.lang.OutOfMemoryError

--->Running <xerces-dom> benchmarks:
-> xmlgen 4 KB
Initialisation time 76.166 + 2.282(4.86%) ms
XSL Transformation Time 6.111(2.38%) ms
-> xmlgen 256 KB
Initialisation time 7.604 + 2.423(67.15%) ms
XSL Transformation Time 276.664(0.73%) ms
-> xmlgen 4 MB
Initialisation time 7.607 + 0.000(0.00%) ms
XSL Transformation Time 5506.050(0.67%) ms

************* Huge XML's Parsing ****************

---> 64 MB ( All other failed )
->Running <expat> benchmarks:
Initialisation time 0.046 + 843.648(0.09%) ms, Parsing Time 1794.231(0.04%) ms
->Running <expat-arabica-sax> benchmarks:
Initialisation time 0.013 + 17.917(108.85%) ms, Parsing Time 39949.175(0.05%) ms
->Running <expat-cslxml-dom> benchmarks:
Initialisation time 0.030 + 0.000(0.00%) ms, Parsing Time 23910.157(0.28%) ms
->Running <expat-cslxml-sax> benchmarks:
Initialisation time 0.008 + 2.413(67.83%) ms, Parsing Time 6768.050(0.02%) ms
->Running <libxml> benchmarks:
Initialisation time 0.172 + 0.000(0.00%) ms, Parsing Time 7184.273(0.87%) ms
->Running <libxml-dom> benchmarks:
Initialisation time 12.177 + 0.000(0.00%) ms, Parsing Time 7141.125(1.24%) ms
->Running <libxml-sax> benchmarks:
Initialisation time 0.002 + 0.446(835.12%) ms, Parsing Time 2147.994(0.17%) ms
->Running <oracle-dom> benchmarks:
Initialisation time 54.732 + 529.824(5.13%) ms, Parsing Time 3525.000(0.77%) ms
->Running <oracle-dom++> benchmarks:
Initialisation time 39.457 + 516.983(6.15%) ms, Parsing Time 3511.799(0.90%) ms
->Running <oracle-sax> benchmarks:
Initialisation time 38.870 + 88.359(45.46%) ms, Parsing Time 3451.610(1.16%) ms
->Running <oracle-sax++> benchmarks:
Initialisation time 48.958 + 86.569(79.53%) ms, Parsing Time 3454.399(1.99%) ms
->Running <qt-sax> benchmarks:
Initialisation time 0.240 + 87.787(113.43%) ms, Parsing Time 79873.836(0.12%) ms
->Running <rxp> benchmarks:
Initialisation time 7.059 + 0.000(0.00%) ms, Parsing Time 10130.505(0.15%) ms
->Running <xerces-dom> benchmarks:
Initialisation time 22.344 + 0.000(0.00%) ms, Parsing Time 14463.219(0.49%) ms
->Running <xerces-sax> benchmarks:
Initialisation time 0.494 + 1.407(1528.56%) ms, Parsing Time 5643.706(0.38%) ms
->Running <xml4c-dom> benchmarks:
Initialisation time 0.199 + 0.000(0.00%) ms, Parsing Time 14479.380(0.61%) ms
->Running <xml4c-sax> benchmarks:
Initialisation time 0.500 + 2.661(781.54%) ms, Parsing Time 5652.865(0.37%) ms

---> 128 MB ( All other failed )
->Running <expat> benchmarks:
Initialisation time 11.076 + 1697.029(0.00%) ms, Parsing Time 3590.309(0.00%) ms
->Running <expat-arabica-sax> benchmarks:
Initialisation time 0.012 + 48.508(0.00%) ms, Parsing Time 79936.358(0.00%) ms
->Running <expat-cslxml-dom> benchmarks:
Initialisation time 0.029 + 0.000(0.00%) ms, Parsing Time 48350.941(0.00%) ms
->Running <expat-cslxml-sax> benchmarks:
Initialisation time 0.008 + 17.128(0.00%) ms, Parsing Time 13561.488(0.00%) ms
->Running <libxml-sax> benchmarks:
Initialisation time 0.002 + 2.243(0.00%) ms, Parsing Time 4345.949(0.00%) ms
->Running <oracle-sax> benchmarks:
Initialisation time 37.502 + 0.000(0.00%) ms, Parsing Time 7123.606(0.00%) ms
->Running <oracle-sax++> benchmarks:
Initialisation time 57.822 + 0.000(0.00%) ms, Parsing Time 7130.558(0.00%) ms
->Running <qt-sax> benchmarks:
Initialisation time 0.245 + 0.000(0.00%) ms, Parsing Time 160252.709(0.00%) ms
->Running <xerces-sax> benchmarks:
Initialisation time 24.921 + 0.000(0.00%) ms, Parsing Time 11297.239(0.00%) ms
->Running <xml4c-sax> benchmarks:
Initialisation time 28.386 + 1.961(0.00%) ms, Parsing Time 11290.374(0.00%) ms

---> 256 MB ( All other failed )
->Running <expat> benchmarks:
Initialisation time 12.208 + 3385.234(0.00%) ms, Parsing Time 7212.832(0.00%) ms
->Running <expat-arabica-sax> benchmarks:
Initialisation time 0.013 + 92.228(0.00%) ms, Parsing Time 159892.150(0.00%) ms
->Running <expat-cslxml-sax> benchmarks:
Initialisation time 0.022 + 65.174(0.00%) ms, Parsing Time 27002.035(0.00%) ms
->Running <libxml-sax> benchmarks:
Initialisation time 0.002 + 23.478(0.00%) ms, Parsing Time 8832.721(0.00%) ms
->Running <oracle-sax> benchmarks:
Initialisation time 42.652 + 468.064(0.00%) ms, Parsing Time 13807.597(0.00%) ms
->Running <oracle-sax++> benchmarks:
Initialisation time 49.430 + 468.126(0.00%) ms, Parsing Time 13819.140(0.00%) ms
->Running <xerces-sax> benchmarks:
Initialisation time 32.318 + 15.645(0.00%) ms, Parsing Time 22568.475(0.00%) ms
->Running <xml4c-sax> benchmarks:
Initialisation time 0.503 + 6.263(0.00%) ms, Parsing Time 22563.885(0.00%) ms

---> 512 MB ( All other failed )
->Running <xerces-sax> benchmarks:
Initialisation time 44.262 + 0.000(0.00%) ms, Parsing Time 45199.531(0.00%) ms
->Running <xml4c-sax> benchmarks:
Initialisation time 0.524 + 12.227(0.00%) ms, Parsing Time 45095.730(0.00%) ms

