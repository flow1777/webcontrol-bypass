#include <httplib.h>
#include <iostream>
#include <fstream>
#include <sstream>

std::string load_file( const std::string &filename )
{
	std::ifstream file( filename );
	if ( !file.is_open( ) )
	{
		return "Cant open file";
	}
	std::stringstream buffer;
	buffer << file.rdbuf( );
	return buffer.str( );
}

void inject( )
{
	std::cout << "Inject is done" << std::endl;
}

void cleaner( )
{
	std::cout << "cleaner is done" << std::endl;
}

int main( )
{
	httplib::Server srv;

	srv.Get( "/", [ ]( const httplib::Request &, httplib::Response &res )
	{
		std::string html = load_file( "./index.html" );
		res.set_content( html, "text/html" );
	} );
	srv.Get( "/inject", [ ]( const httplib::Request &, httplib::Response &res )
	{
		inject( );
		res.set_content( "Inject Finished", "text/html" );
	} );

	srv.Get( "/cleaner", [ ]( const httplib::Request &, httplib::Response &res )
	{
		cleaner( );
		res.set_content( "Cleaner Finished", "text/html" );
	} );
	

	std::cout << "O servidor foi iniciado com sucesso" << std::endl;
	srv.listen( "0.0.0.0", 8080 );
}