idf_component_register(SRCS "kiss_fft.c" "tools/fftutil.c" 
                        "tools/kfc.c" 
                        "tools/kiss_fastfir.c" 
                        "tools/kiss_fftnd.c" 
                        "tools/kiss_fftndr.c" 
                        "tools/kiss_fftr.c"
                        INCLUDE_DIRS "." "tools"
                        REQUIRES "driver")

