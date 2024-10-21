Configuration:
    P4 2.2GHZ / i850E / 1GB RDRAM
    Linux 2.4.22 / glibc 2.3.2 / gcc 3.3.1, 2.96 
    Libraries as described in README

******************** Parsing Benchmarks ********************

--->Running <expat> benchmarks:
-> xmlgen 4 KB
Initialisation time 0.019 + 0.081(8.75%) ms, Parsing Time 0.132(5.33%) ms
-> xmlgen 256 KB
Initialisation time 0.021 + 1.778(6.15%) ms, Parsing Time 9.062(1.21%) ms
-> xmlgen 32 MB
Initialisation time 0.031 + 137.593(15.08%) ms, Parsing Time 1129.735(1.84%) ms
-> opcgen 50 ( 3.5KB )
Parsing Time 9857.613000 ms for 80000 messages
-> opcgen 50000 ( 3 MB )
Parsing Time 11902.892000 ms for 100 messages
-> dmoz rdf file ( 12 MB )
Initialisation time 0.030 + 37.247(26.28%) ms, Parsing Time 294.210(3.33%) ms
--->Running <expat-arabica-dom> benchmarks:
-> xmlgen 4 KB
Initialisation time 0.002 + 0.540(6.97%) ms, Parsing Time 5.904(0.64%) ms
-> xmlgen 256 KB
Initialisation time 0.002 + 22.959(3.75%) ms, Parsing Time 453.109(0.19%) ms
-> xmlgen 32 MB
./runbench.1: line 31:  1573 Killed                  ./$name `expr $time "*" 8` xmlgen 32000000
-> opcgen 50 ( 3.5KB )
Parsing Time 347561.600000 ms for 80000 messages
-> opcgen 50000 ( 3 MB )
./runbench.1: line 31:  1577 Killed                  ./$name `expr $time "*" 100` opcgen 50000
-> dmoz rdf file ( 12 MB )
Initialisation time 0.002 + 75.343(31.82%) ms, Parsing Time 7479.428(0.32%) ms
--->Running <expat-arabica-sax> benchmarks:
-> xmlgen 4 KB
Initialisation time 0.007 + 0.272(9.72%) ms, Parsing Time 2.568(1.03%) ms
-> xmlgen 256 KB
Initialisation time 0.007 + 0.000(0.00%) ms, Parsing Time 201.098(0.44%) ms
-> xmlgen 32 MB
Initialisation time 0.013 + 31.672(175.89%) ms, Parsing Time 24745.434(0.23%) ms
-> opcgen 50 ( 3.5KB )
Parsing Time 135863.134000 ms for 80000 messages
-> opcgen 50000 ( 3 MB )
Parsing Time 177022.298000 ms for 100 messages
-> dmoz rdf file ( 12 MB )
Initialisation time 0.012 + 0.000(0.00%) ms, Parsing Time 3019.080(0.39%) ms
--->Running <expat-cslxml-dom> benchmarks:
-> xmlgen 4 KB
Initialisation time 0.024 + 1.129(1.63%) ms, Parsing Time 1.411(1.31%) ms
-> xmlgen 256 KB
Initialisation time 0.024 + 1.079(35.58%) ms, Parsing Time 92.065(0.42%) ms
-> xmlgen 32 MB
Initialisation time 0.036 + 0.000(0.00%) ms, Parsing Time 11356.826(0.52%) ms
-> opcgen 50 ( 3.5KB )
Parsing Time 137798.054000 ms for 80000 messages
-> opcgen 50000 ( 3 MB )
Parsing Time 155243.869000 ms for 100 messages
-> dmoz rdf file ( 12 MB )
Initialisation time 0.035 + 7.807(92.44%) ms, Parsing Time 2456.419(0.29%) ms
--->Running <expat-cslxml-sax> benchmarks:
-> xmlgen 4 KB
Initialisation time 0.005 + 11.757(0.09%) ms, Parsing Time 0.448(2.41%) ms
-> xmlgen 256 KB
Initialisation time 0.005 + 0.335(76.53%) ms, Parsing Time 28.401(0.90%) ms
-> xmlgen 32 MB
Initialisation time 0.008 + 15.657(230.77%) ms, Parsing Time 3478.792(1.04%) ms
-> opcgen 50 ( 3.5KB )
Parsing Time 51356.819000 ms for 80000 messages
-> opcgen 50000 ( 3 MB )
Parsing Time 62091.425000 ms for 100 messages
-> dmoz rdf file ( 12 MB )
Initialisation time 0.009 + 0.000(0.00%) ms, Parsing Time 1022.075(0.05%) ms
--->Running <expat-sablotron-dom> benchmarks:
-> xmlgen 4 KB
Initialisation time 18.985 + 3.422(0.54%) ms, Parsing Time 1.469(1.26%) ms
-> xmlgen 256 KB
Initialisation time 0.095 + 1.557(27.44%) ms, Parsing Time 96.284(0.44%) ms
-> xmlgen 32 MB
Initialisation time 0.114 + 108.163(53.60%) ms, Parsing Time 11841.323(0.49%) ms
-> opcgen 50 ( 3.5KB )
Parsing Time 96871.643000 ms for 80000 messages
-> opcgen 50000 ( 3 MB )
Parsing Time 111567.618000 ms for 100 messages
-> dmoz rdf file ( 12 MB )
Initialisation time 0.101 + 0.000(0.00%) ms, Parsing Time 2035.364(0.31%) ms
--->Running <libxml> benchmarks:
-> xmlgen 4 KB
Initialisation time 0.101 + 0.246(4.52%) ms, Parsing Time 0.433(2.57%) ms
-> xmlgen 256 KB
Initialisation time 0.105 + 0.000(0.00%) ms, Parsing Time 33.891(1.33%) ms
-> xmlgen 32 MB
Initialisation time 0.137 + 0.000(0.00%) ms, Parsing Time 4245.846(0.83%) ms
-> opcgen 50 ( 3.5KB )
Parsing Time 31505.640000 ms for 80000 messages
-> opcgen 50000 ( 3 MB )
Parsing Time 48831.225000 ms for 100 messages
-> dmoz rdf file ( 12 MB )
Initialisation time 0.137 + 0.000(0.00%) ms, Parsing Time 1444.915(1.28%) ms
--->Running <libxml-dom> benchmarks:
-> xmlgen 4 KB
Initialisation time 9.785 + 5.007(0.24%) ms, Parsing Time 0.570(2.14%) ms
-> xmlgen 256 KB
Initialisation time 0.023 + 0.000(0.00%) ms, Parsing Time 42.924(0.94%) ms
-> xmlgen 32 MB
Initialisation time 0.030 + 0.000(0.00%) ms, Parsing Time 5332.007(0.71%) ms
-> opcgen 50 ( 3.5KB )
Parsing Time 45328.296000 ms for 80000 messages
-> opcgen 50000 ( 3 MB )
Parsing Time 64828.047000 ms for 100 messages
-> dmoz rdf file ( 12 MB )
Initialisation time 0.030 + 0.000(0.00%) ms, Parsing Time 1734.853(1.34%) ms
--->Running <libxml-push> benchmarks:
-> xmlgen 4 KB
Initialisation time 0.142 + 0.259(4.58%) ms, Parsing Time 0.549(2.16%) ms
-> xmlgen 256 KB
Initialisation time 0.155 + 0.000(0.00%) ms, Parsing Time 44.986(4.90%) ms
-> xmlgen 32 MB
Initialisation time 0.187 + 0.000(0.00%) ms, Parsing Time 5649.721(0.80%) ms
-> opcgen 50 ( 3.5KB )
Parsing Time 44326.091000 ms for 80000 messages
-> opcgen 50000 ( 3 MB )
Parsing Time 65450.563000 ms for 100 messages
-> dmoz rdf file ( 12 MB )
Initialisation time 0.178 + 0.000(0.00%) ms, Parsing Time 1654.301(2.04%) ms
--->Running <libxml-sax> benchmarks:
-> xmlgen 4 KB
Initialisation time 0.002 + 0.252(2.79%) ms, Parsing Time 0.159(4.42%) ms
-> xmlgen 256 KB
Initialisation time 0.002 + 1.254(17.08%) ms, Parsing Time 9.798(2.19%) ms
-> xmlgen 32 MB
Initialisation time 0.002 + 0.000(0.00%) ms, Parsing Time 1285.889(0.63%) ms
-> opcgen 50 ( 3.5KB )
Parsing Time 12198.505000 ms for 80000 messages
-> opcgen 50000 ( 3 MB )
Parsing Time 13700.148000 ms for 100 messages
-> dmoz rdf file ( 12 MB )
Initialisation time 0.002 + 2.874(73.19%) ms, Parsing Time 432.529(0.49%) ms
--->Running <oracle-dom> benchmarks:
-> xmlgen 4 KB
Initialisation time 103.423 + 7.949(0.11%) ms, Parsing Time 0.526(1.67%) ms
-> xmlgen 256 KB
Initialisation time 1.673 + 0.431(29.01%) ms, Parsing Time 13.357(0.94%) ms
-> xmlgen 32 MB
Initialisation time 1.857 + 6.058(357.75%) ms, Parsing Time 1578.879(1.37%) ms
-> opcgen 50 ( 3.5KB )
Parsing Time 80640.853000 ms for 80000 messages
-> opcgen 50000 ( 3 MB )
Parsing Time 38946.534000 ms for 100 messages
-> dmoz rdf file ( 12 MB )
Initialisation time 1.734 + 11.193(84.93%) ms, Parsing Time 1487.609(0.64%) ms
--->Running <oracle-dom++> benchmarks:
-> xmlgen 4 KB
Initialisation time 125.081 + 2.352(0.35%) ms, Parsing Time 0.571(1.46%) ms
-> xmlgen 256 KB
Initialisation time 1.703 + 0.352(24.49%) ms, Parsing Time 12.833(0.67%) ms
-> xmlgen 32 MB
Initialisation time 1.829 + 4.059(54.67%) ms, Parsing Time 1519.814(0.15%) ms
-> opcgen 50 ( 3.5KB )
Parsing Time 84064.185000 ms for 80000 messages
-> opcgen 50000 ( 3 MB )
Parsing Time 42601.397000 ms for 100 messages
-> dmoz rdf file ( 12 MB )
Initialisation time 1.752 + 0.000(0.00%) ms, Parsing Time 1541.814(0.73%) ms
--->Running <oracle-sax> benchmarks:
-> xmlgen 4 KB
Initialisation time 20.592 + 2.720(0.29%) ms, Parsing Time 0.514(1.52%) ms
-> xmlgen 256 KB
Initialisation time 1.653 + 0.144(127.87%) ms, Parsing Time 10.354(1.78%) ms
-> xmlgen 32 MB
Initialisation time 1.835 + 0.000(0.00%) ms, Parsing Time 1218.776(1.00%) ms
-> opcgen 50 ( 3.5KB )
Parsing Time 78579.592000 ms for 80000 messages
-> opcgen 50000 ( 3 MB )
Parsing Time 40474.105000 ms for 100 messages
-> dmoz rdf file ( 12 MB )
Initialisation time 1.738 + 0.686(1819.94%) ms, Parsing Time 1475.107(0.85%) ms
--->Running <oracle-sax++> benchmarks:
-> xmlgen 4 KB
Initialisation time 137.713 + 24.508(0.03%) ms, Parsing Time 0.545(1.50%) ms
-> xmlgen 256 KB
Initialisation time 1.676 + 0.000(0.00%) ms, Parsing Time 10.718(3.38%) ms
-> xmlgen 32 MB
Initialisation time 1.874 + 0.000(0.00%) ms, Parsing Time 1194.223(0.53%) ms
-> opcgen 50 ( 3.5KB )
Parsing Time 75137.377000 ms for 80000 messages
-> opcgen 50000 ( 3 MB )
Parsing Time 40622.122000 ms for 100 messages
-> dmoz rdf file ( 12 MB )
Initialisation time 1.776 + 17.712(90.07%) ms, Parsing Time 1473.198(1.08%) ms
--->Running <oracle_dom2> benchmarks:
-> xmlgen 4 KB
Initialisation time 243.0 + 89.13589411764706(1.9151204392811676%) ms
Parsing Time 0.8641058823529412(197.5521474677146%)
-> xmlgen 256 KB
Initialisation time 162.0 + 195.648(28.382465194013157%) ms
Parsing Time 79.352(69.9789866705097%)
-> xmlgen 32 MB
Exception in thread "main" java.lang.OutOfMemoryError
-> opcgen 50 ( 3.5KB )
Parsing Time 68343.0 ms for 80000 messages
-> opcgen 50000 ( 3 MB )
Exception in thread "main" java.lang.OutOfMemoryError
-> dmoz rdf file ( 12 MB )
Initialisation time 163.0 + 757.96(7.034471093135729%) ms
Parsing Time 1630.04(3.270991944831512%)
--->Running <oracle_sax2> benchmarks:
-> xmlgen 4 KB
Initialisation time 162.0 + 58.40602352941176(3.059518266873586%) ms
Parsing Time 0.5939764705882353(300.84406492855965%)
-> xmlgen 256 KB
Initialisation time 162.0 + 109.504(22.677832704806754%) ms
Parsing Time 22.496(110.38910884189006%)
-> xmlgen 32 MB
Initialisation time 162.0 + 232.5(5.933079056011458%) ms
Parsing Time 2617.5(0.5270070221672069%)
-> opcgen 50 ( 3.5KB )
Parsing Time 40393.0 ms for 80000 messages
-> opcgen 50000 ( 3 MB )
Parsing Time 27659.0 ms for 100 messages
-> dmoz rdf file ( 12 MB )
Initialisation time 162.0 + 155.24(21.622327465955124%) ms
Parsing Time 922.76(3.6376198749565147%)
--->Running <qt-dom> benchmarks:
-> xmlgen 4 KB
Initialisation time 0.011 + 31.310(0.08%) ms, Parsing Time 3.255(0.79%) ms
-> xmlgen 256 KB
Initialisation time 0.010 + 0.000(0.00%) ms, Parsing Time 213.345(0.48%) ms
-> xmlgen 32 MB
Initialisation time 0.014 + 0.000(0.00%) ms, Parsing Time 25584.706(0.18%) ms
-> opcgen 50 ( 3.5KB )
Parsing Time 208299.933000 ms for 80000 messages
-> opcgen 50000 ( 3 MB )
Parsing Time 222457.634000 ms for 100 messages
-> dmoz rdf file ( 12 MB )
Initialisation time 0.015 + 0.000(0.00%) ms, Parsing Time 3810.344(0.86%) ms
--->Running <qt-sax> benchmarks:
-> xmlgen 4 KB
Initialisation time 0.072 + 2.187(1.28%) ms, Parsing Time 3.746(0.75%) ms
-> xmlgen 256 KB
Initialisation time 0.076 + 1.599(40.30%) ms, Parsing Time 238.621(0.27%) ms
-> xmlgen 32 MB
Initialisation time 0.095 + 4.981(1071.77%) ms, Parsing Time 29055.286(0.18%) ms
-> opcgen 50 ( 3.5KB )
Parsing Time 218078.142000 ms for 80000 messages
-> opcgen 50000 ( 3 MB )
Parsing Time 227578.437000 ms for 100 messages
-> dmoz rdf file ( 12 MB )
Initialisation time 0.090 + 6.806(183.64%) ms, Parsing Time 4390.297(0.28%) ms
--->Running <rxp> benchmarks:
-> xmlgen 4 KB
Initialisation time 11.889 + 0.100(12.34%) ms, Parsing Time 0.388(3.20%) ms
-> xmlgen 256 KB
Initialisation time 0.874 + 0.366(98.52%) ms, Parsing Time 38.805(0.93%) ms
-> xmlgen 32 MB
Initialisation time 0.949 + 0.000(0.00%) ms, Parsing Time 4824.297(0.43%) ms
-> opcgen 50 ( 3.5KB )
Parsing Time 22998.931000 ms for 80000 messages
-> opcgen 50000 ( 3 MB )
Parsing Time 38787.692000 ms for 100 messages
-> dmoz rdf file ( 12 MB )
Initialisation time 0.905 + 0.000(0.00%) ms, Parsing Time 1060.099(0.51%) ms
--->Running <sun_dom2> benchmarks:
-> xmlgen 4 KB
Initialisation time 103.0 + 96.86642352941176(6.016842823354319%) ms
Parsing Time 1.1335764705882352(514.1515022224298%)
-> xmlgen 256 KB
Initialisation time 64.0 + 205.515(26.620460777306437%) ms
Parsing Time 61.485(88.97949087823261%)
-> xmlgen 32 MB
Exception in thread "main" java.lang.OutOfMemoryError
-> opcgen 50 ( 3.5KB )
Parsing Time 92435.0 ms for 80000 messages
-> opcgen 50000 ( 3 MB )
Exception in thread "main" java.lang.OutOfMemoryError
-> dmoz rdf file ( 12 MB )
Initialisation time 60.0 + 725.56(10.129459448227376%) ms
Parsing Time 1367.44(5.374664041753828%)
--->Running <sun_sax2> benchmarks:
-> xmlgen 4 KB
Initialisation time 68.0 + 79.4522(2.402143405547054%) ms
Parsing Time 0.5478(348.40375736802787%)
-> xmlgen 256 KB
Initialisation time 61.0 + 142.994(5.793488559170074%) ms
Parsing Time 22.006(37.64582854812167%)
-> xmlgen 32 MB
Initialisation time 60.0 + 300.75(14.793006406049903%) ms
Parsing Time 2587.25(1.719585148949467%)
-> opcgen 50 ( 3.5KB )
Parsing Time 44400.0 ms for 80000 messages
-> opcgen 50000 ( 3 MB )
Parsing Time 32239.0 ms for 100 messages
-> dmoz rdf file ( 12 MB )
Initialisation time 60.0 + 197.08000000000004(6.087629256915498%) ms
Parsing Time 786.92(1.5246149214061235%)
--->Running <xerces-dom> benchmarks:
-> xmlgen 4 KB
Initialisation time 2.072 + 27.825(0.06%) ms, Parsing Time 1.035(1.48%) ms
-> xmlgen 256 KB
Initialisation time 0.275 + 1.453(28.45%) ms, Parsing Time 67.398(0.61%) ms
-> xmlgen 32 MB
Initialisation time 0.311 + 45.393(100.98%) ms, Parsing Time 8136.813(0.56%) ms
-> opcgen 50 ( 3.5KB )
Parsing Time 83923.438000 ms for 80000 messages
-> opcgen 50000 ( 3 MB )
Parsing Time 91321.103000 ms for 100 messages
-> dmoz rdf file ( 12 MB )
Initialisation time 0.289 + 44.040(62.42%) ms, Parsing Time 1750.640(1.57%) ms
--->Running <xerces-sax> benchmarks:
-> xmlgen 4 KB
Initialisation time 0.571 + 0.594(1.60%) ms, Parsing Time 0.331(2.86%) ms
-> xmlgen 256 KB
Initialisation time 0.596 + 3.674(8.64%) ms, Parsing Time 21.412(1.48%) ms
-> xmlgen 32 MB
Initialisation time 0.671 + 393.582(3.27%) ms, Parsing Time 2551.442(0.50%) ms
-> opcgen 50 ( 3.5KB )
Parsing Time 32479.879000 ms for 80000 messages
-> opcgen 50000 ( 3 MB )
Parsing Time 34858.351000 ms for 100 messages
-> dmoz rdf file ( 12 MB )
Initialisation time 0.643 + 0.000(0.00%) ms, Parsing Time 969.123(0.35%) ms


******************** DOM Tree Build Benchmarks ********************

--->Running <expat-cslxml-dom> benchmarks:
-> 5KB file (20)
Building DOM tree in 2.860(0.49) ms!
-> 500KB file (2500)
Building DOM tree in 366.586(0.81) ms!
-> 9MB file (50000)
Building DOM tree in 212926.586(0.81) ms!
--->Running <expat-sablotron-dom> benchmarks:
-> 5KB file (20)
Building DOM tree in 2.858(0.48) ms!
-> 500KB file (2500)
Building DOM tree in 293.607(0.21) ms!
-> 9MB file (50000)
Building DOM tree in 9233.556(0.29) ms!
--->Running <libxml> benchmarks:
-> 5KB file (20)
Building DOM tree in 0.763(0.95) ms!
-> 500KB file (2500)
Building DOM tree in 95.172(0.74) ms!
-> 9MB file (50000)
Building DOM tree in 1950.631(0.67) ms!
--->Running <libxml-dom> benchmarks:
-> 5KB file (20)
Building DOM tree in 2.989(0.63) ms!
-> 500KB file (2500)
Building DOM tree in 348.378(1.07) ms!
-> 9MB file (50000)
Building DOM tree in 7573.681(0.36) ms!
--->Running <oracle-dom> benchmarks:
-> 5KB file (20)
Building DOM tree in 0.439(1.32) ms!
-> 500KB file (2500)
Building DOM tree in 28.871(1.00) ms!
-> 9MB file (50000)
Building DOM tree in 585.591(1.26) ms!
--->Running <oracle-dom++> benchmarks:
-> 5KB file (20)
Building DOM tree in 0.446(1.52) ms!
-> 500KB file (2500)
Building DOM tree in 29.681(1.86) ms!
-> 9MB file (50000)
Building DOM tree in 598.859(1.44) ms!
--->Running <oracle_dom2> benchmarks:
-> 5KB file (20)
Creating DOM Tre Time 1.2661698113207547(110.88602805973416%) ms
-> 500KB file (2500)
Creating DOM Tre Time 256.7527777777778(5.217041649733912%) ms
-> 9MB file (50000)
Exception in thread "main" java.lang.OutOfMemoryError
--->Running <qt-dom> benchmarks:
-> 5KB file (20)
Building DOM tree in 2.720(0.53) ms!
-> 500KB file (2500)
Building DOM tree in 286.338(0.58) ms!
-> 9MB file (50000)
Building DOM tree in 5815.451(0.41) ms!
--->Running <sun_dom2> benchmarks:
-> 5KB file (20)
Creating DOM Tre Time 0.6635283018867925(238.70301663692746%) ms
-> 500KB file (2500)
Creating DOM Tre Time 173.34166666666667(5.853721981716433%) ms
-> 9MB file (50000)
Exception in thread "main" java.lang.OutOfMemoryError
--->Running <xerces-dom> benchmarks:
-> 5KB file (20)
Building DOM tree in 1.607(0.54) ms!
-> 500KB file (2500)
Building DOM tree in 152.301(0.50) ms!
-> 9MB file (50000)
Building DOM tree in 3018.865(0.44) ms!


******************** Schema Validating Benchmarks ********************

--->Running <libxml> benchmarks:
-> xmlgen 4 KB
Initialisation time 15.528 + 0.037(48.95%) ms, Validation Time 0.203(9.04%) ms
-> xmlgen 256 KB
Initialisation time 0.747 + 0.000(0.00%) ms, Validation Time 15.142(1.41%) ms
-> opcgen 50 ( 3.5KB )
Validating Time 513.266000 ms for 1600 messages
-> opcgen 50000 ( 3 MB ) - 4 times longer
Validating Time 33993.857000 ms for 100 messages
--->Running <oracle-dom> benchmarks:
-> xmlgen 4 KB
Initialisation time 16.256 + 6.244(0.61%) ms, Validation Time 0.445(8.59%) ms
-> xmlgen 256 KB
Initialisation time 1.900 + 0.000(0.00%) ms, Validation Time 15.178(4.00%) ms
-> opcgen 50 ( 3.5KB )
Validating Time 2237.234000 ms for 1600 messages
-> opcgen 50000 ( 3 MB ) - 4 times longer
./runbench.3: line 48:  1381 Killed                  ./$name `expr $time "*" 100` opcgen 50000
--->Running <sun_dom2> benchmarks:
-> xmlgen 4 KB
Initialisation time 8.0 + 97.7591011235955(6.792572302055839%) ms
Parsing Time 3.126292134831461(820.5448583909699%)
-> xmlgen 256 KB
Initialisation time 8.0 + 194.5263157894737(24.638141913676616%) ms
Parsing Time 67.3859649122807(170.15450103721676%)
-> opcgen 50 ( 3.5KB )
Parsing Time 34451.0 ms for 1600 messages
-> opcgen 50000 ( 3 MB ) - 4 times longer
Exception in thread "main" java.lang.OutOfMemoryError
--->Running <xerces-dom> benchmarks:
-> xmlgen 4 KB
Initialisation time 0.001 + 34.288(0.18%) ms, Validation Time 2.955(3.56%) ms
-> xmlgen 256 KB
Initialisation time 0.001 + 1.358(59.23%) ms, Validation Time 57.754(2.85%) ms
-> opcgen 50 ( 3.5KB )
Validating Time 22777.085000 ms for 1600 messages
-> opcgen 50000 ( 3 MB ) - 4 times longer
Validating Time 101006.933000 ms for 100 messages


************* XSL Transformation Benchmarks ****************

--->Running <expat-sablotron-dom> benchmarks:
-> xmlgen 4 KB
Initialisation time 3.240 + 0.000(0.00%) ms
XSL Transformation Time 14.639(1.13%) ms
-> xmlgen 256 KB
Initialisation time 2.196 + 15.790(19.49%) ms
XSL Transformation Time 613.037(0.50%) ms
-> xmlgen 4 MB
Initialisation time 2.256 + 0.000(0.00%) ms
XSL Transformation Time 10714.960(0.24%) ms
--->Running <libxml> benchmarks:
-> xmlgen 4 KB
Initialisation time 12.216 + 0.297(22.89%) ms
XSL Transformation Time 2.528(2.69%) ms
-> xmlgen 256 KB
Initialisation time 0.856 + 3.233(38.73%) ms
XSL Transformation Time 108.057(1.16%) ms
-> xmlgen 4 MB
Initialisation time 0.872 + 38.441(22.26%) ms
XSL Transformation Time 1690.688(0.51%) ms
--->Running <oracle-dom> benchmarks:
-> xmlgen 4 KB
Initialisation time 1.138 + 21.338(0.29%) ms
XSL Transformation Time 3.310(1.86%) ms
-> xmlgen 256 KB
Initialisation time 1.172 + 0.000(0.00%) ms
XSL Transformation Time 113.102(0.95%) ms
-> xmlgen 4 MB
Initialisation time 1.268 + 204.762(16.47%) ms
XSL Transformation Time 6044.312(0.56%) ms
--->Running <sun_dom2> benchmarks:
-> xmlgen 4 KB
Initialisation time 271.0 + 128.98986666666667(25.165982216998344%) ms
XSL Transformation Time 7.010133333333333(463.0663264663993%)
-> xmlgen 256 KB
Initialisation time 247.0 + 648.6542857142857(12.26004143103633%) ms
XSL Transformation Time 304.3457142857143(26.129917537825847%)
-> xmlgen 4 MB
Exception in thread "main" java.lang.OutOfMemoryError
--->Running <xerces-dom> benchmarks:
-> xmlgen 4 KB
Initialisation time 47.935 + 1.720(5.24%) ms
XSL Transformation Time 4.793(2.58%) ms
-> xmlgen 256 KB
Initialisation time 5.742 + 5.160(32.15%) ms
XSL Transformation Time 202.366(1.08%) ms
-> xmlgen 4 MB
Initialisation time 5.741 + 0.000(0.00%) ms
XSL Transformation Time 4276.492(0.88%) ms


********** Security (Signature/Encryption)  Benchmarks *************

--->Running <libxml1> benchmarks:
-> xmlgen 4 KB
Initialisation time 80.005 + 2.431(8.42%) ms
Signing/Verifying Time 4.231(2.35%) ms
Encrypting/Decrypting Time 4.853(2.17%) ms
-> xmlgen 256 KB
Initialisation time 6.155 + 11.598(53.74%) ms
Signing/Verifying Time 172.806(1.97%) ms
Encrypting/Decrypting Time 184.379(1.54%) ms
-> opcgen 50 ( 3.5KB )
Signing/Verifying Time 20109.649000 ms for 5300 messages
Encrypting/Decrypting Time 27166.335000 ms for 5300 messages
-> opcgen 50000 ( 3 MB ) - 4 times longer
Signing/Verifying Time 179660.884000 ms for 100 messages
Encrypting/Decrypting Time 284545.167000 ms for 100 messages
-> dmoz rdf file ( 12 MB ) - 4 times longer
Initialisation time 6.038 + 95.935(78.41%) ms
Signing/Verifying Time 3163.245(1.15%) ms
Encrypting/Decrypting Time 7162.101(0.54%) ms
--->Running <sun_dom2> benchmarks:
-> xmlgen 4 KB
Initialisation Time: 881.0 + 613.306(4.462707472619538%) ms
Signing/Verifying Time: 452.6906666666667(6.007881167844448%)
Encryption/Decryption Time: 0.0033333333333333335(5188.061423035031%)
-> xmlgen 256 KB
Exception in thread "main" java.lang.OutOfMemoryError
-> opcgen 50 ( 3.5KB )
Signing/Verifiying Time: 1461907.0 ms for 5300 messages
Encryption/Decryption Time: 18.0 ms for 5300 messages
-> opcgen 50000 ( 3 MB ) - 4 times longer
Exception in thread "main" java.lang.OutOfMemoryError
-> dmoz rdf file ( 12 MB ) - 4 times longer
Exception in thread "main" java.lang.OutOfMemoryError
--->Running <xerces-dom> benchmarks:
-> xmlgen 4 KB
Initialisation time 12.718 + 0.613(352.35%) ms
Signing/Verifying Time 34.393(5.26%) ms
Encrypting/Decrypting Time 11.592(3.01%) ms
-> xmlgen 256 KB
Initialisation time 1.148 + 488.636(3.03%) ms
Signing/Verifying Time 3890.580(0.26%) ms
Encrypting/Decrypting Time 747.369(0.60%) ms
-> opcgen 50 ( 3.5KB )
Signing/Verifying Time 172885.554000 ms for 5300 messages
Encrypting/Decrypting Time 59580.017000 ms for 5300 messages
-> opcgen 50000 ( 3 MB ) - 4 times longer
./runbench.3: line 32:  1201 Killed                  ./$name `expr $time "*" 100` opcgen 50000
-> dmoz rdf file ( 12 MB ) - 4 times longer
Signing/Verifying Time 1314979.731(0.00%) ms
Encrypting/Decrypting Time Error decrypting: E
