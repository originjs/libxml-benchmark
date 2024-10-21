******************** Parsing Benchmarks ********************

--->Running <libxml> benchmarks:
-> xmlgen 256 KB
Initialisation time 12.217 + 2.309(14.52%) ms, Parsing Time 25.166(1.33%) ms
-> opcgen 50 ( 3.5KB )
Parsing Time 21069.632000 ms for 80000 messages
-> dmoz rdf file ( 12 MB )
Initialisation time 0.129 + 0.000(0.00%) ms, Parsing Time 1127.314(1.70%) ms
--->Running <libxml-sax> benchmarks:
-> xmlgen 256 KB
Initialisation time 0.001 + 0.984(19.89%) ms, Parsing Time 9.737(2.01%) ms
-> opcgen 50 ( 3.5KB )
Parsing Time 9739.738000 ms for 80000 messages
-> dmoz rdf file ( 12 MB )
Initialisation time 0.002 + 1.138(154.03%) ms, Parsing Time 408.769(0.43%) ms
--->Running <libxml-push> benchmarks:
-> xmlgen 256 KB
Initialisation time 0.094 + 0.000(0.00%) ms, Parsing Time 32.781(6.69%) ms
-> opcgen 50 ( 3.5KB )
Parsing Time 25156.156000 ms for 80000 messages
-> dmoz rdf file ( 12 MB )
Initialisation time 0.127 + 0.000(0.00%) ms, Parsing Time 1287.773(2.72%) ms
--->Running <libxml-dom> benchmarks:
-> xmlgen 256 KB
Initialisation time 10.060 + 0.000(0.00%) ms, Parsing Time 29.880(1.62%) ms
-> opcgen 50 ( 3.5KB )
Parsing Time 26925.319000 ms for 80000 messages
-> dmoz rdf file ( 12 MB )
Initialisation time 0.028 + 0.000(0.00%) ms, Parsing Time 1287.608(1.32%) ms


******************** DOM Tree Build Benchmarks ********************

--->Running <libxml> benchmarks:
-> 5KB file (20)
Building DOM tree in 0.471(1.34) ms!
-> 500KB file (2500)
Building DOM tree in 65.428(1.25) ms!
-> 9MB file (50000)
Building DOM tree in 1338.037(0.99) ms!


******************** Schema Validating Benchmarks ********************

--->Running <libxml> benchmarks:
-> xmlgen 4 KB
Initialisation time 7.162 + 0.030(50.43%) ms, Validation Time 0.150(9.99%) ms
-> xmlgen 256 KB
Initialisation time 0.619 + 0.000(0.00%) ms, Validation Time 11.016(3.90%) ms
-> opcgen 50 ( 3.5KB )
Validating Time 327.219000 ms for 1600 messages


************* XSL Transformation Benchmarks ****************

--->Running <libxml> benchmarks:
-> xmlgen 4 KB
Initialisation time 5.514 + 0.284(19.49%) ms
XSL Transformation Time 1.628(3.40%) ms
-> xmlgen 256 KB
Initialisation time 0.718 + 3.896(26.46%) ms
XSL Transformation Time 60.446(1.71%) ms
-> xmlgen 4 MB
Initialisation time 0.715 + 56.361(11.81%) ms
XSL Transformation Time 942.179(0.71%) ms


********** Security (Signature/Encryption)  Benchmarks *************

--->Running <libxml1> benchmarks:
-> xmlgen 256 KB
Initialisation time 81.214 + 6.023(105.81%) ms
Signing/Verifying Time 134.891(2.54%) ms
Encrypting/Decrypting Time 166.353(1.77%) ms
-> opcgen 50 ( 3.5KB )
Signing/Verifying Time 17165.070000 ms for 5300 messages
Encrypting/Decrypting Time 24662.481000 ms for 5300 messages
-> dmoz rdf file ( 12 MB ) - 4 times longer
Initialisation time 5.555 + 191.208(28.16%) ms
Signing/Verifying Time 2511.237(0.82%) ms
Encrypting/Decrypting Time 6928.731(0.48%) ms
