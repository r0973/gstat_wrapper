// Example program
#include <iostream>
#include <fstream>
#include <string>

template<typename vector_t>
struct gstat_vario {
    public:
        using value_type = typename vector_t::value_type;
    
    public:
        vector_t m_d;
        vector_t av_dist;
        vector_t gamma;
        vector_t h;
        size_t np;   

    static void make_variogramm (
        const vector_t& x,
        const vector_t& y,
        const vector_t& z,
        const typename vector_t::value_type width = 0,
        const typename vector_t::value_type cutoff = 0,
        std::string method = "semivariogram"
    )
    {
        std::ofstream ofs;
        
        ofs.open("sample_data.dat", std::ios::out);    
        
        for(auto itx = x.cbegin(), 
                 ity = y.cbegin(),
                 itz = z.cbegin();
                 itx != x.cend() &&
                 ity != y.cend() &&
                 itz != z.cend();
                 ++itx, ++ity, ++itz
        )
        {
             ofs << *itx << "   " << *ity << "   " << *itz << "\n";   
        }
        
        //write gstat command file
        ofs.close();
        
        ofs.open("sample_vario.cmd", std::ios::out);
        
        ofs << "data(Vario): ''sample_data'', x=1, y=2, v=3;" << "\n";
        ofs << "method: " << method << "\n";
        ofs << "variogram(Vario): ''sample_vario.out'';" << "\n";
        
        if(width)
        {
            ofs << "set width: " << width << "\n";
        }
        
        if(cutoff)
        {
            ofs << "set cutoff" << "\n";    
        }
        
        ofs.close();
        
#ifdef _MSC_VER 
        std::system('gstat.exe sample_vario.cmd');
#elif defined(__GNUC__) 
        std::system('gstat sample_vario.cmd');
#endif
        
        //Read the resulting file
        std::ifstream ifs('sample_vario.out', std::ios::in);
        std::string line;
        for( auto i=0; i<8; ++i)
        {
            std::getline(ifs,line);    
        }
        
        value_type dd;
    
        ifs >> dd;
        
        ofs.close();
    
    }

};
