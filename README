Development Environment Setup
=============================

1.  Install Embarcadero C++ Builder XE2

2.  Build MFC. See `release/data/readme_mfc.txt`

    For source code from C++ Builder 6, see `release\libs\mfc`

3.  Build OpenSSL

        mkdir release\libs\lib
        cd release\libs\openssl
        make
        mkdir source\openssl\openssl
        copy release\libs\openssl\openssl\*.* source\openssl\openssl

4.  Run C++ Builder

5.  Set following environment variables user overrides 

    (go to *Tools > Options > Environment Options > Environment Variables > User overrides*)

        INTERM_PATH=<path to generate intermediate files to, can be set to .>    
        FINAL_PATH=<path to generate final files to, can be set to .>
        WINSCPTRACE=off (to turn off tracing while debugging)

6.  Copy `ssleay32.lib` and `libeay32.lib` to INTERM_PATH\Debug and INTERM_PATH\Release

7.  Open `WinSCP.groupproj`

8.  Build and install all `.bpl` projects

9.  Force rebuild of `RScpComp.lib`
    (it shares intermediate output files with `DScpComp.lib`)

10. Build all other projects
