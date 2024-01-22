
add_library(proc ./include/pipeline_reg.h
		 		 ./src/pipeline_reg.cpp
				 ./include/regfile.h
		 		 ./src/regfile.cpp
				 ./include/alu.h
		 		 ./src/alu.cpp
				 ./include/instr_mem.h
		 		 ./src/instr_mem.cpp
				 ./include/seqproc.h
				 )
