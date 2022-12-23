#include <pipc/process/process.hpp>
#include <pipc/fifo/fifo.hpp>

int main(){
	pipc::process p("ls");
	return 0;
}