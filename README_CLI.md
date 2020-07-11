lofar_udp_extractor
===================
The *lofar_udp_extractor* utility can be used to extract and process LOFAR beamformed observations from international stations.


Expected Input Formats
---------------------
The expected recoridng format consists of the last 16-bytes of the header (all ethernet/udp frames removed) followed by the *N* byte data payload. 


Multiple ports of data can be processed at once by providing a *%d* in the input file name. This will iterate from 0 to the specifed number of ports (*-u* flag) and concatenate the frequencies into a single output outside of processing mode 0.

Any times are handled in the ISOT format (YYYY-MM-DDTHH:mm:ss, fractions of seconds are not supported) in UTC+0 (NOT effected by local time zone, summer, etc unless your station clock has been modified).

The events file format is described at the end of this document.

Example Command
---------------
```
./lofar_udp_extractor -i "./udp_1613%d.ucc1.2020-02-22T10:30:00.000.zst" -u 4 \
		-o "./test_output_%d_%s_%ld" \
		-m 100000 -p 100\
		-t "2020-02-22T11:02:00" -s 360.5

```
This command
- Takes an input from 4 ports of date (16130 -> 16133) from a set of files in the local folder
- Outputs it to a file, with a suffix containing the output number (0->numOutputs, here it will just be 0), starting timestamp (later fixed to 2020-02-22T11:02:00) and the starting packet number
- Sets the number of packets reader + processed per iteration to 100,000
- Sets the output to be a Stokes I array
- Sets the starting point to 2020-02-22T11:02:00, and will only read the next 6 minutes and 0.5 seconds of data

Arguments
--------

#### -i (str)
- Input file name, let it contain *%d* to iterate over a number of ports

#### -o (str) [default: "./output_%d_%s_%ld"]
- Output file name, must contain at least *%d* when generating multiple outputs
- *%s* will include the starting time stamp, *%ld* will include the starting packet number
- These values must be added in order, so *%d_%s* is allowed to not print the packet number but *%ld_%d_%s* will not work.

#### -m (int) [default: 65536]
- Number of packets to read and process per iteration
- Be considerate of the memory requirements for loading / processing the data when setting this value

#### -u (int) [default: 4]
- Number of input ports to iterate over

#### -t (str) [default: T=0]
- Starting time string, in UTC+0 and ISOT format (YYYY-MM-DDTHH:mm:ss)

#### -s (float) [default: FLOAT_MAX]
- Maximum amount of data (in seconds) to process before exiting

#### -e (str) 
- Location of an events file, for processing multiple time / extraction lengths as once, file format described below
- Must have at least *%d* and *%s* in the output name to prevent overwriting each event with the next one

#### -p (int) [default: 0]
- Sets the processing mode for the output (options listed below)

#### -r
- If set, the last good packet will be repeated when a dropped packet is detected
- Default behaviour is to 0 pad the output

#### -c
- If set, change from calculating the start time from the RSP 200MHz clock (Modes 3, 5, 7) to the 160MHz clock (4,6, probably others)

#### -q 
- If set, silence the output from this CLI. Library error messages will still be displayed.

#### -a (str)
- Call mockHeader to generate a header for new files
- By default, we will pass in the number of channels and the starting time


#### -f
- If set, we will append to file rather than overwrite them.
- Do note, using this in conjunction with *-a* will replace files rather than appending them.



Processing Modes
----------------
### Default Ordering Operaitons
#### 0: "Raw Copy"
- Copy the input to the output, padding dropped packets and dropping out of order packets
- 1 input file -> 1 output file


#### 1: "Raw Headerless Copy"
- Copy the input payload data to the output, removing the CEP header, padding dropped packets and dropping out of order packets
- 1 input file -> 1 output file

#### 2: "Raw Split Polarizations"
- Copy the input payload, padding where needed, and splitting across each of the (Xr, Xi, Yr, Yi) polarisations
- N input files -> 4 output files


### Re-ordering Operations
#### 10: "Raw To Beamlet-Majour"
- Take the input payload, padding where needed, remove the header, reorder the data such that instead of having (f0t0, f0t1... f0t15, f1t0...) we have (f0t0, f1t0, f2t0)...
- N input files -> 1 output file

#### 11: "Raw to Beamlet-Majour, Split Polarizations"
- Combintion of (2) and (10), split output data per (Xr, Xi, Yr, Yi) polarizations
- N input files -> 4 output files

#### 20: "Raw To Beamlet-Majour, Frequecy Reversed"
- Modified version of (10), where instead of (f0t0, f1t0...) we now output (fNt0, fN-1t0, ...), following the standard used for pulsar observations
- N input files -> 1 output file

#### 21: "Raw To Beamlet-Majour, Frequency Reversed, Split Polarizations"
- Combination of (2) and (20), where we split the output data per Xr, Xi, Yr, Yi) polarizations
- N input files -> 4 output files


### Processing Operations
#### 100: "Stokes I"
- Take the input data, apply (20) and then combine the polarizations to form a 32-bit floating point Stokes I for each frequency sample
- N input files -> 1 output file

#### 101: "Stokes V"
- Take the input data, apply (20) and then combine the polarizations to form a 32-bit floating point Stokes V for each frequency sample
- N input files -> 1 output file



Event Files
-----------
Event files can be used to extract multiple, non-continuous elements of an observation. The file must
- Have the number of events to process in the first line
- List the events in order from start to finish of the observation
- Not contain events that overlap
```
NUM_EVENTS
ISOT0 LENGTH0
ISOT1 LENGTH1
...
```

For example, in a 2 event case, we could use the file
```
2
2020-02-22T10:02:00 100.33
2020-02-22T11:04:00 300.5
```

While it is possible to extract multiple events from a given second, you will need all three output file characters (*%d*, *%s*, *%ld*) in order to prevent the output files from overlapping (only the *%ld* variable will be changing).