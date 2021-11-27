idf_component_register(SRCS "chem.cpp" 
                            "rationalMatrix.c"
			                "rationalNumber.c" 
                    INCLUDE_DIRS  "."
                    REQUIRED_IDF_TARGETS esp32)
