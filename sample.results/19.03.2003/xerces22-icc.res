******************** Parsing Benchmarks ********************

--->Running <xerces-dom> benchmarks:
-> xmlgen 256 KB
Initialisation time 0.278 + 1.817(68.52%) ms, Parsing Time 49.039(2.54%) ms
-> opcgen 50 ( 3.5KB )
Parsing Time 73791.637000 ms for 80000 messages
-> dmoz rdf file ( 12 MB )
Initialisation time 0.304 + 14.002(70.80%) ms, Parsing Time 1369.210(0.72%) ms
--->Running <xerces-sax> benchmarks:
-> xmlgen 256 KB
Initialisation time 0.540 + 1.175(37.70%) ms, Parsing Time 17.125(2.59%) ms
-> opcgen 50 ( 3.5KB )
Parsing Time 28005.045000 ms for 80000 messages
-> dmoz rdf file ( 12 MB )
Initialisation time 0.575 + 0.000(0.00%) ms, Parsing Time 722.402(0.86%) ms


******************** DOM Tree Build Benchmarks ********************

--->Running <xerces-dom> benchmarks:
-> 5KB file (20)
Building DOM tree in 1.316(1.98) ms!
-> 500KB file (2500)
Building DOM tree in 130.904(1.08) ms!
-> 9MB file (50000)
Building DOM tree in 2614.473(0.36) ms!


******************** Schema Validating Benchmarks ********************

--->Running <xerces-dom> benchmarks:
-> xmlgen 4 KB
Initialisation time 0.001 + 12.587(0.91%) ms, Validation Time 3.386(5.54%) ms
-> xmlgen 256 KB
Initialisation time 0.001 + 4.972(43.85%) ms, Validation Time 102.373(3.14%) ms
-> opcgen 50 ( 3.5KB )
Validating Time 23966.129000 ms for 1600 messages


********** Security (Signature/Encryption)  Benchmarks *************



************* XSL Transformation Benchmarks ****************

