******************** Parsing Benchmarks ********************

--->Running <xerces-dom> benchmarks:
-> xmlgen 256 KB
Initialisation time 0.356 + 24.812(3.65%) ms, Parsing Time 57.673(1.57%) ms
-> opcgen 50 ( 3.5KB )
Parsing Time 86.753000 ms for 100 messages
-> dmoz rdf file ( 12 MB )
Initialisation time 0.354 + 13.604(93.12%) ms, Parsing Time 1873.772(0.68%) ms
--->Running <xerces-sax> benchmarks:
-> xmlgen 256 KB
Initialisation time 0.690 + 0.000(0.00%) ms, Parsing Time 23.275(5.18%) ms
-> opcgen 50 ( 3.5KB )
Parsing Time 35.256000 ms for 100 messages
-> dmoz rdf file ( 12 MB )
Initialisation time 0.696 + 0.000(0.00%) ms, Parsing Time 1190.880(1.35%) ms


******************** DOM Tree Build Benchmarks ********************

--->Running <xerces-dom> benchmarks:
-> 5KB file (20)
Building DOM tree in 1.667(2.27) ms!
-> 500KB file (2500)
Building DOM tree in 159.861(1.58) ms!
-> 9MB file (50000)
Building DOM tree in 3224.418(0.97) ms!


******************** Schema Validating Benchmarks ********************

--->Running <xerces-dom> benchmarks:
-> xmlgen 4 KB
Initialisation time 0.001 + 118.653(0.13%) ms, Validation Time 3.845(6.34%) ms
-> xmlgen 256 KB
Initialisation time 0.001 + 0.000(0.00%) ms, Validation Time 119.760(3.14%) ms
-> opcgen 50 ( 3.5KB )
Validating Time 27756.596000 ms for 1600 messages


********** Security (Signature/Encryption)  Benchmarks *************



************* XSL Transformation Benchmarks ****************

