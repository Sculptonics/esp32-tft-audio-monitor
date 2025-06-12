idf_component_register(SRCS "Processor.cpp" "HammingWindow.cpp"
                      INCLUDE_DIRS "." 
                      REQUIRES "driver" "kissfft")