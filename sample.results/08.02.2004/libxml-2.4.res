******************** Parsing Benchmarks ********************

--->Running <libxml> benchmarks:
-> xmlgen 256 KB
Initialisation time 0.159 + 0.000(0.00%) ms, Parsing Time 47.233(3.33%) ms
-> opcgen 50 ( 3.5KB )
Parsing Time 46722.338000 ms for 80000 messages
-> dmoz rdf file ( 12 MB )
Initialisation time 0.182 + 0.000(0.00%) ms, Parsing Time 1650.884(0.54%) ms
--->Running <libxml-sax> benchmarks:
-> xmlgen 256 KB
Initialisation time 0.002 + 1.092(24.83%) ms, Parsing Time 13.387(2.03%) ms
-> opcgen 50 ( 3.5KB )
Parsing Time 15972.126000 ms for 80000 messages
-> dmoz rdf file ( 12 MB )
Initialisation time 0.001 + 0.000(0.00%) ms, Parsing Time 577.726(1.15%) ms


******************** DOM Tree Build Benchmarks ********************

--->Running <libxml> benchmarks:
-> 5KB file (20)
Building DOM tree in 0.756(1.06) ms!
-> 500KB file (2500)
Building DOM tree in 91.048(1.32) ms!
-> 9MB file (50000)
Building DOM tree in 1894.245(0.56) ms!
--->Running <libxml-dom> benchmarks:
-> 5KB file (20)
Building DOM tree in 3.172(0.52) ms!
-> 500KB file (2500)
Building DOM tree in 363.401(1.07) ms!
-> 9MB file (50000)
Building DOM tree in 7275.058(0.39) ms!


************* XSL Transformation Benchmarks ****************

--->Running <libxml> benchmarks:
-> xmlgen 4 KB
Initialisation time 0.897 + 0.212(32.49%) ms
XSL Transformation Time 2.571(2.68%) ms
-> xmlgen 256 KB
Initialisation time 0.975 + 1.166(119.12%) ms
XSL Transformation Time 112.222(1.24%) ms
-> xmlgen 4 MB
Initialisation time 0.979 + 1.029(1052.65%) ms
XSL Transformation Time 1756.797(0.62%) ms


********** Security (Signature/Encryption)  Benchmarks *************

--->Running <libxml> benchmarks:
-> xmlgen 256 KB
Initialisation time 45.813 + 0.000(0.00%) ms
Signing/Verifying Time 158.636(1.08%) ms
Encrypting/Decrypting Time 213.391(2.39%) ms
-> opcgen 50 ( 3.5KB )
Signing/Verifying Time 17327.142000 ms for 5300 messages
Encrypting/Decrypting Time 23389.945000 ms for 5300 messages
-> dmoz rdf file ( 12 MB ) - 4 times longer
Initialisation time 4.291 + 0.000(0.00%) ms
Signing/Verifying Time 2878.605(1.46%) ms
Encrypting/Decrypting Time 8800.911(0.54%) ms
