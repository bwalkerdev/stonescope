# Touchstone Specification Rev 1.1
## Table of Contents
1. Introduction
2. Genral Syntax and Guidelines
3. File Format Description
3.1 Introduction
3.2 Option Line
3.2.1 Option Line examples
3.3 Data lines
3.4 1 and 2 port networks 
3.4.1 Example 1
3.4.2 Example 2
3.4.3 Example 3
3.4.4 Example 4
3.5 3-port and 4-port Networks
3.4.1 Example 5
3.6 5-port and above networks
3.6.1 Example 6
3.7 Comment Lines
3.8 Adding Noise Parameters 
3.8.1 Example 8

## Introduction
A Touchstone® file (also known as an SnP file) is an ASCII text file
used for documenting the n-port network parameter data of an active
device or passive interconnect network. While Touchstone files have
been accepted as a de-facto standard for the transfer of frequency
dependent n-port network data, up till now there has been no formal
documentation of the file format or syntax. This document, based upon
information from Agilent Corporation (the originator of Touchstone), is
a formal specification of the Touchstone file format, intended for use
with documents and specifications produced by the EIA/IBIS Open Forum.

## General Syntax and Guidelines
Following are the general syntax rules and guidelines for a Touchstone
file.
1. Touchstone file are case-insensitive.
2. Only ASCII characters, as defined in ANSI Standard X3.4-1986, may be
used in a Touchstone file. The use of characters with codes greater
than hexadecimal 07E is not allowed. Also, ASCII control characters
(those numerically less than hexadecimal 20) are not allowed, except
for tabs or in a line termination sequence (carriage-return or
carriage-return/line-feed combination).
Note: The use of Tab characters is strongly discouraged.
3. Comments are preceded by an exclamation mark (!). Comments may
appear on a separate line, or after the last data value on a line.
Comments are terminated by a line termination sequence (i.e. multi-
line comments are not allowed).
4. By convention, Touchstone filenames use a file extension of ‘.snp’,
where “n” is the number of network ports of the device or
interconnect being described. For example, a Touchstone file
containing the network parameters for a two port device would be
named ‘filename’.s2p, while a Touchstone file containing the data
for a 3-port network would be ‘filename’.s3p, and so on.
5. By convention, angles are measured in degrees.

## File Format Description
### Introduction
Touchstone data files consist of an ‘option line’ followed by one or
more sets of network parameter data, where each set of data is taken at
a specific frequency. The option line specifies (among other things)
the kind of network data the file contains (S-parameter, Z-parameter,
etc.), the format of the data values (magnitude-phase, real-imaginary,
etc.) and the normalizing impedance. Data sets are arranged into one
or more ‘data lines’, where the first line of network data is preceded
by the frequency at which the data was taken or derived. Data for a 1-
port or 2-port network are contained on a single data line while data
for 3-port and above networks are arrayed in a matrix format. The
Touchstone format supports matrixes of unlimited size. (Note, however,
many application programs and/or available computer memory will set an
upper bound on how much data a Touchstone file can contain).
Only one option-line/data-set pair is allowed per file.
In addition to the above option lines and data lines, files that
describe 2-port devices may also contain noise parameter data.
Finally, comment lines can be interspersed in the file as necessary.
The option line, data line, comment line and noise data are described
in detail in the following sub-sections.
### Option Line
Each Touchstone data file must contain an option line (additional
option lines after the first one will be ignored). The option line
must be the first non-comment line of the file, and is formatted as
follows:
\# <frequency unit> <parameter> <format> R <n>
where
\# marks the beginning of the option line.
frequency unit specifies the unit of frequency. Legal values are
GHz, MHz, KHz, Hz. The default value is GHz.
parameter specifies what kind of network parameter data is
contained in the file. Legal values are:
S for Scattering parameters,
Y for Admittance parameters,
Z for Impedance parameters,
H for Hybrid-h parameters,
G for Hybrid-g parameters.
The default value is S
format specifies the format of the network parameter data pairs. Legal values are:
DB for dB-angle (dB = 20*log10|magnitude|)
MA for magnitude-angle,
RI for real-imaginary.
Angles are given in degrees. Note that this format
does not apply to noise parameters. (Refer to the
“Adding Noise Parameters” section at the end of this
document). The default value is MA.
R n specifies the reference resistance in ohms, where n
is a positive number of ohms (the real impedance to
which the parameters are normalized). The default
reference resistance is 50 ohms.
Option line parameters are separated by one or more whitespace; the
option line itself is terminated with a newline character (either CR or
CR/LF). If a parameter is missing it assumes the default value. With
the exception of the opening # (hash mark) symbol and the value
following “R”, option line parameters can appear in any order.
In summary, the option line should read:
For 1-port files: # [HZ/KHZ/MHZ/GHZ] [S/Y/Z/G/H] [MA/DB/RI] [R n]
For 2-port files: # [HZ/KHZ/MHZ/GHZ] [S/Y/Z/G/H] [MA/DB/RI] [R n]
For n-port files: # [HZ/KHZ/MHZ/GHZ] [S/Y/Z/G/H] [MA/DB/RI] [R n]
where the square brackets ([]) indicate optional information;
.../.../.../ means select one of the choices; and n is replaced by a
positive number.

#### Option Line Examples
Minimum required option line (using all default values)
\#
Frequency in GHz, S-parameters in real-imaginary format, normalized to
100 ohms:
\# GHz S RI R 100
Frequency in KHz, Y-parameters in real-imaginary format, normalized to
100 ohms:
\# KHz Y RI R 100
Frequency in Hz, Z-parameters in magnitude-angle format, normalized to
1 ohm:
\# Hz Z MA R 1
Frequency in KHz, H-parameters in real-imaginary format normalized to 1
ohm:
\# KHz H RI R 1
Frequency in Hz, G-parameters in magnitude-angle, format normalized to
1 ohm:
\# Hz G MA R 1

### Data Lines
Following the option line is the data set. Data sets contain the data
for the network parameters (S-parameter, Z-parameter, etc.) specified
by the option line. Network data for 1-port and 2-port networks is
contained on one data line, while data for 3-port and above are
arranged on multiple data lines in a matrix format. Each set of
network data is preceded by a frequency value (i.e. the first entry in
the first (or only) data line of a data set is a frequency value), and
the network data itself is formatted as pairs of values (magnitude-
angle, dB-angle or real-imaginary).
There are three general rules for formatting data lines and data sets:
1. No more than four pairs of network data are allowed per data line.
2. Individual entries in a data lines are separated by whitespace
3. A data line is terminated by a newline character (CR or CR/LF
combination).
4. All data sets must be arranged in increasing order of frequency.
Detailed descriptions for arranging the data for various n-port
networks follows.

### 1 and 2 Port networks
Network parameter data for 1-port and 2-port networks at a single
frequency can be contained on a single data line. As shown below, the
data line consists of a frequency value followed by either one or four
pairs of data values.
1-port data set (line)
<frequency value> <N11>
2-port data set (line)
<frequency value> <N11>, <N21>, <N12>, <N22>
Where
frequency value frequency at which the network parameter data
was taken or derived.
N11, N21, N12, N22 network parameter data points, where N11, N21,
etc. represent pairs of data values
Network parameter data points will be in magnitude-angle, dB-angle or
real-imaginary format (i.e. pairs of values) as specified by the option
line. For 1-port networks only ‘11’ data is allowed, while for 2-port
networks all four combinations are required.
Note the order in which 2-port network data is entered – ‘21’ data
precedes ‘12’ data.
All entries in a data line are separated by one or more whitespace; a
data line itself is terminated by a newline character (CR or CR/LF).
Multiple data lines (sets) are allowed, but as mentioned above they
must be arranged in increasing order of frequency. 
Following are some examples of Touchstone files for 1-port and 2-port
networks. Lines beginning with a bang (!) symbol are comments.

#### Example 1
!1-port S-parameter file, single frequency point
\# MHz S MA R 50
!freq magS11 angS11
2.000 0.894 -12.136
In the above example, the value of S11 at a frequency of 2MhZ is given
in magnitude-angle format. The reference impedance is 50 ohms.

#### Example 2:
!1-port Z-parameter file, multiple frequency points
\# MHz Z MA R 75
!freq magZ11 angZ11
100 0.99 -4
200 0.80 -22
300 0.707 -45
400 0.40 -62
500 0.01 -89
Note that in the above example Z11 (the input impedance) is normalized
to 75 ohms, as given by the reference impedance (R 75) in the option
line.

#### Example 3:
!2-port H-parameter file, single frequency point
\# KHz H MA R 1
! freq magH11 angH11 magH21 angH21 magH12 angH12 magH22 angH22
2 .95 -26 3.57 157 .04 76 .66 -14
In the above example the H-parameters are given in magnitude-angle
format, with a reference impedance of 1 ohm.
#### Example 4:
!2-port S-parameter file, three frequency points
\# GHZ S RI R 50.0
!freq RelS11 ImS11 ReS21 ImS21 ReS12 ImS12 ReS22 ImS22
1.0000 0.3926 -0.1211 -0.0003 -0.0021 -0.0003 -0.0021 0.3926 -0.1211
2.0000 0.3517 -0.3054 -0.0096 -0.0298 -0.0096 -0.0298 0.3517 -0.3054
10.000 0.3419 0.3336 -0.0134 0.0379 -0.0134 0.0379 0.3419 0.3336
In the above example the S-parameter data is given in real-imaginary
format

### 3-port and 4-port networks
The network parameter data for a 3-port or 4-port network is arranged
in a matrix format, with each line of data representing one row of the
matrix. In other words (as shown below), the data for a 3-port network is entered as three lines of data, with each line containing three data
pairs (i.e. a 3x3 matrix of network parameter values). Likewise, the
data for a 4-port network is entered as four lines with four data pairs
per line (a 4x4 matrix). As required by the general rules, the first
data line of each network parameter data set is preceded by the
frequency value at which the data was taken.
3-port network description
<frequency value> <N11> <N12> <N13>
<N21> <N22> <N23>
<N31> <N32> <N33>
4-port network description
<frequency value> <N11> <N12> <N13> <N14>
<N21> <N22> <N23> <N24>
<N31> <N32> <N33> <N34>
<N41> <N42> <N43> <N44>
Where
frequency value frequency at which the network parameter data
was taken or derived.
N11, N12, etc. network parameter data points, where Nij
represent pairs of data values.
As usual, network parameter data points are entered in magnitude-angle,
dB-angle or real-imaginary format (i.e. pairs of values) as specified
by the option line. All entries in a data line are separated by one or
more whitespace; a data line itself is terminated by a newline
character (CR or CR/LF). Multiple data sets are allowed, but as
mentioned above they must be arranged in increasing order of frequency.
Following is an example of an S-parameter description of a 4-port
network.

#### Example 5:
! 4-port S-parameter data, taken at three frequency points
\# GHZ S MA R 50
5.00000 0.60 161.24 0.40 -42.20 0.42 -66.58 0.53 -79.34 !row 1
0.40 -42.20 0.60 161.20 0.53 -79.34 0.42 -66.58 !row 2
0.42 -66.58 0.53 -79.34 0.60 161.24 0.40 -42.20 !row 3
0.53 -79.34 0.42 -66.58 0.40 -42.20 0.60 161.24 !row 4
6.00000 0.57 150.37 0.40 -44.34 0.41 -81.24 0.57 -95.77 !row 1
0.40 -44.34 0.57 150.37 0.57 -95.77 0.41 -81.24 !row 2
0.41 -81.24 0.57 -95.77 0.57 150.37 0.40 -44.34 !row 3
0.57 -95.77 0.41 -81.24 0.40 -44.34 0.57 150.37 !row 4
7.00000 0.50 136.69 0.45 -46.41 0.37 -99.09 0.62 -114.19 !row 1
0.45 -46.41 0.50 136.69 0.62 -114.19 0.37 -99.09 !row 2
0.37 -99.09 0.62 -114.19 0.50 136.69 0.45 -46.41 !row 3
0.62 -114.19 0.37 -99.09 0.45 -46.41 0.50 136.69 !row 4
Note that the data pairs do not have to be aligned in columns; the only
requirement is that there be 3 (3-port networks) or 4 (4-port networks)
pairs of network data per data line.

### 5-port and above Networks
The network data for 5-port and above networks is also arranged in a
matrix format. However, because the Touchstone format is limited to a
maximum of 4 network parameter data points per line, additional entries
beyond the first four in the matrix row must be continued on the
following line(s). Each row of the matrix must start on a new line.
As usual, the first entry in the first data line of a data set is the
frequency value. These rules are illustrated by showing the format for
a 6-port network:
6-port network format (single frequency point)
<frequency value> <N11> <N12> <N13> <N14> !row 1
<N15> <N16>
<N21> <N22> <N23> <N24> !row 2
<N25> <N26>
<N31> <N32> <N33> <N34> !row 3
<N35> <N36>
<N41> <N42> <N43> <N44> !row 4
<N45> <N46>
<N51> <N52> <N53> <N54> !row 5
<N55> <N56>
<N61> <N62> <N63> <N64> !row 6
<N65> <N66>
Where
frequency value frequency at which the network parameter data
was taken or derived.
N11, N12, etc. network parameter data points, where Nij
represent pairs of data values.
As shown, each row of matrix data extends over two lines of the file,
and each new row of the matrix starts on a new line. As usual, network
data values are entered in pairs according to the format specified in
the option line and each entry is separated by whitespace.
Following is a more detailed example illustrating the data matrix for a
10-port network. The Y-parameter data is in magnitude-angle format,
and is for a single frequency.

#### Example 6:
\# frequency_unit Y MA R impedance
freq magY11 angY11 magY12 angY12 magY13 angY13 magY14 angY14 ! 1st row
magY15 angY15 magY16 angY16 magY17 angY17 magY18 angY18
magY19 angY19 magY1,10 angY1,10
magY21 angY21 magY22 angY22 magY23 angY23 magY24 angY24 ! 2nd row
magY25 angY25 magY26 angY26 magY27 angY27 magY28 angY28
magY29 angY29 magY2,10 angY2,10
magY31 angY31 magY32 angY32 magY33 angY33 magY34 angY34 ! 3rd row
magY35 angY35 magY36 angY36 magY37 angY37 magY38 angY38
magY39 angY39 magY3,10 angY3,10

magY41 angY41 magY42 angY42 magY43 angY43 magY44 angY44 ! 4th row
magY45 angY45 magY46 angY46 magY47 angY47 magY48 angY48
magY49 angY49 magY4,10 angY4,10
magY51 angY51 magY52 angY52 magY53 angY53 magY54 angY54 ! 5th row
magY55 angY55 magY56 angY56 magY57 angY57 magY58 angY58
magY59 angY59 magY5,10 angY5,10
magY61 angY61 magY62 angY62 magY63 angY63 magY64 angY64 ! 6th row
magY65 angY65 magY66 angY66 magY67 angY67 magY68 angY68
magY69 angY69 magY6,10 angY6,10
magY71 angY71 magY72 angY72 magY73 angY73 magY74 angY74 ! 7th row
magY75 angY75 magY76 angY76 magY77 angY77 magY78 angY78
magY79 angY79 magY7,10 angY7,10
magY81 angY81 magY82 angY82 magY83 angY83 magY84 angY84 ! 8th row
magY85 angY85 magY86 angY86 magY87 angY87 magY88 angY88
magY89 angY89 magY8,10 angY8,10
magY91 angY91 magY92 angY92 magY93 angY93 magY94 angY94 ! 9th row
magY95 angY95 magY96 angY96 magY97 angY97 magY98 angY98
magY99 angY99 magY9,10 angY9,10
!10th row
magY10,1 angY10,1 magY10,2 angY10,2 magY10,3 angY10,3 magY10,4 angY10,4
magY10,5 angY10,5 magY10,6 angY10,6 magY10,7 angY10,7 magY10,8 angY10,8
magY10,9 angY10,9 magY10,10 angY10,10

### Comment Lines
A Touchstone data files can be documented by preceding a comment with
the exclamation mark (!). A comment can be the only entry on a line or
can follow the data on any line.

### Adding Noise Parameters
Noise parameters can be included in Touchstone data file, however, they
can only be included in 2-port network descriptions. Noise data follows
the G-, H-, S-, Y-, or Z-parameters data for each frequency point.
Each line of a noise parameter has the following five entries:
<x1> <x2> <x3> <x4> <x5>
where
x1 Frequency in units. The first point of noise data must have a
frequency less than the frequency of the last S-parameter
frequency.
x2 Minimum noise figure in dB.
x3 Source reflection coefficient to realize minimum noise figure
(MA).
x4 Phase in degrees of the reflection coefficient (MA).
x5 Normalized effective noise resistance. A simulator requires this
parameter to meet physical requirements. If the user-supplied x5
value is less than allowed for this requirement, then a simulator
may force this x5 value to the lowest physical limit.

Note that the frequencies for noise parameters and network parameters
need not match. The only requirement is that the lowest noise-parameter
frequency be less than or equal to the highest network-parameter
frequency. This allows the file processor to determine where network
parameters end and noise parameters begin.
The source reflection coefficient and effective noise resistance are
normalized to the same resistance as specified in the option line for
the network parameters.
#### Example 8:
!2-port network, S-parameter and noise data
\# GHZ S MA R 50
2 .95 -26 3.57 157 .04 76 .66 -14
22 .60 -144 1.30 40 .14 40 .56 -85
! NOISE PARAMETERS
4 .7 .64 69 .38
18 2.7 .46 -33 .40
