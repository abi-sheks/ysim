
add_library(proc ./include/reg.h
		 		 ./src/reg.cpp
				 ./include/regfile.h
		 		 ./src/regfile.cpp
				 ./include/alu.h
		 		 ./src/alu.cpp
				 ./include/instr_mem.h
		 		 ./src/instr_mem.cpp
				 ./include/seqproc.h
				 ./src/seqproc.cpp
				 ./include/cnd_flags.h
				 )
