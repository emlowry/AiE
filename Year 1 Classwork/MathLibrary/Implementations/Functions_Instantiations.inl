/******************************************************************************
 * File:               Functions_Instantiations.inl
 * Author:             Elizabeth Lowry
 * Date Created:       March 5, 2014
 * Description:        Explicit instantiations for template functions.
 * Last Modified:      March 5, 2014
 * Last Modification:  Creation.
 ******************************************************************************/

#ifndef FUNCTIONS__INSTANTIATIONS__INL
#define FUNCTIONS__INSTANTIATIONS__INL

#include "../Declarations/Functions.h"
#include <type_traits>
#include "../Declarations/ImExportMacro.h"

// explicitly instantiate Modulo and ModuloAssign for float with common types
EXTERN_T_INST template IMEXPORT_T_INST
    std::common_type< float, float >::type
    Math::Modulo< float, float >( const float& ac_rDividend,
                                  const float& ac_rDivisor );
EXTERN_T_INST template IMEXPORT_T_INST
    float& Math::ModuloAssign< float, float >( float& a_rDividend,
                                               const float& ac_rDivisor );
EXTERN_T_INST template IMEXPORT_T_INST
    std::common_type< float, double >::type
    Math::Modulo< float, double >( const float& ac_rDividend,
                                   const double& ac_rDivisor );
EXTERN_T_INST template IMEXPORT_T_INST
    float& Math::ModuloAssign< float, double >( float& a_rDividend,
                                                const double& ac_rDivisor );
EXTERN_T_INST template IMEXPORT_T_INST
    std::common_type< float, unsigned int >::type
    Math::Modulo< float, unsigned int >( const float& ac_rDividend,
                                         const unsigned int& ac_rDivisor );
EXTERN_T_INST template IMEXPORT_T_INST
    float& Math::ModuloAssign< float, unsigned int >( float& a_rDividend,
                                                      const unsigned int& ac_rDivisor );
EXTERN_T_INST template IMEXPORT_T_INST
    std::common_type< float, int >::type
    Math::Modulo< float, int >( const float& ac_rDividend,
                                const int& ac_rDivisor );
EXTERN_T_INST template IMEXPORT_T_INST
    float& Math::ModuloAssign< float, int >( float& a_rDividend,
                                             const int& ac_rDivisor );

// explicitly instantiate Modulo and ModuloAssign for double with common types
EXTERN_T_INST template IMEXPORT_T_INST
    std::common_type< double, float >::type
    Math::Modulo< double, float >( const double& ac_rDividend,
                                   const float& ac_rDivisor );
EXTERN_T_INST template IMEXPORT_T_INST
    double& Math::ModuloAssign< double, float >( double& a_rDividend,
                                                 const float& ac_rDivisor );
EXTERN_T_INST template IMEXPORT_T_INST
    std::common_type< double, double >::type
    Math::Modulo< double, double >( const double& ac_rDividend,
                                    const double& ac_rDivisor );
EXTERN_T_INST template IMEXPORT_T_INST
    double& Math::ModuloAssign< double, double >( double& a_rDividend,
                                                  const double& ac_rDivisor );
EXTERN_T_INST template IMEXPORT_T_INST
    std::common_type< double, unsigned int >::type
    Math::Modulo< double, unsigned int >( const double& ac_rDividend,
                                          const unsigned int& ac_rDivisor );
EXTERN_T_INST template IMEXPORT_T_INST
    double& Math::ModuloAssign< double, unsigned int >( double& a_rDividend,
                                                        const unsigned int& ac_rDivisor );
EXTERN_T_INST template IMEXPORT_T_INST
    std::common_type< double, int >::type
    Math::Modulo< double, int >( const double& ac_rDividend,
                                 const int& ac_rDivisor );
EXTERN_T_INST template IMEXPORT_T_INST
    double& Math::ModuloAssign< double, int >( double& a_rDividend,
                                               const int& ac_rDivisor );

// explicitly instantiate Modulo and ModuloAssign for unsigned int with common types
EXTERN_T_INST template IMEXPORT_T_INST
    std::common_type< unsigned int, float >::type
    Math::Modulo< unsigned int, float >( const unsigned int& ac_rDividend,
                                         const float& ac_rDivisor );
EXTERN_T_INST template IMEXPORT_T_INST
    unsigned int& Math::ModuloAssign< unsigned int, float >( unsigned int& a_rDividend,
                                                             const float& ac_rDivisor );
EXTERN_T_INST template IMEXPORT_T_INST
    std::common_type< unsigned int, double >::type
    Math::Modulo< unsigned int, double >( const unsigned int& ac_rDividend,
                                          const double& ac_rDivisor );
EXTERN_T_INST template IMEXPORT_T_INST
    unsigned int& Math::ModuloAssign< unsigned int, double >( unsigned int& a_rDividend,
                                                              const double& ac_rDivisor );
EXTERN_T_INST template IMEXPORT_T_INST
    std::common_type< unsigned int, unsigned int >::type
    Math::Modulo< unsigned int, unsigned int >( const unsigned int& ac_rDividend,
                                                const unsigned int& ac_rDivisor );
EXTERN_T_INST template IMEXPORT_T_INST
    unsigned int& Math::ModuloAssign< unsigned int, unsigned int >( unsigned int& a_rDividend,
                                                                    const unsigned int& ac_rDivisor );
EXTERN_T_INST template IMEXPORT_T_INST
    std::common_type< unsigned int, int >::type
    Math::Modulo< unsigned int, int >( const unsigned int& ac_rDividend,
                                       const int& ac_rDivisor );
EXTERN_T_INST template IMEXPORT_T_INST
    unsigned int& Math::ModuloAssign< unsigned int, int >( unsigned int& a_rDividend,
                                                           const int& ac_rDivisor );

// explicitly instantiate Modulo and ModuloAssign for int with common types
EXTERN_T_INST template IMEXPORT_T_INST
    std::common_type< int, float >::type
    Math::Modulo< int, float >( const int& ac_rDividend,
                                      const float& ac_rDivisor );
EXTERN_T_INST template IMEXPORT_T_INST
    int& Math::ModuloAssign< int, float >( int& a_rDividend,
                                           const float& ac_rDivisor );
EXTERN_T_INST template IMEXPORT_T_INST
    std::common_type< int, double >::type
    Math::Modulo< int, double >( const int& ac_rDividend,
                                        const double& ac_rDivisor );
EXTERN_T_INST template IMEXPORT_T_INST
    int& Math::ModuloAssign< int, double >( int& a_rDividend,
                                            const double& ac_rDivisor );
EXTERN_T_INST template IMEXPORT_T_INST
    std::common_type< int, unsigned int >::type
    Math::Modulo< int, unsigned int >( const int& ac_rDividend,
                                           const unsigned int& ac_rDivisor );
EXTERN_T_INST template IMEXPORT_T_INST
    int& Math::ModuloAssign< int, unsigned int >( int& a_rDividend,
                                                  const unsigned int& ac_rDivisor );
EXTERN_T_INST template IMEXPORT_T_INST
    std::common_type< int, int >::type
    Math::Modulo< int, int >( const int& ac_rDividend,
                                  const int& ac_rDivisor );
EXTERN_T_INST template IMEXPORT_T_INST
    int& Math::ModuloAssign< int, int >( int& a_rDividend,
                                         const int& ac_rDivisor );

// Explicitly instantiate Scroll for some common types
EXTERN_T_INST template IMEXPORT_T_INST
    float Math::Scroll< float >( const float& ac_rValue,
                                 const float& ac_rMax,
                                 const float& ac_rMin );
EXTERN_T_INST template IMEXPORT_T_INST
    double Math::Scroll< double >( const double& ac_rValue,
                                   const double& ac_rMax,
                                   const double& ac_rMin );
EXTERN_T_INST template IMEXPORT_T_INST
    unsigned int Math::Scroll< unsigned int >( const unsigned int& ac_rValue,
                                               const unsigned int& ac_rMax,
                                               const unsigned int& ac_rMin );
EXTERN_T_INST template IMEXPORT_T_INST
    int Math::Scroll< int >( const int& ac_rValue,
                             const int& ac_rMax,
                             const int& ac_rMin );

#endif  // FUNCTIONS__INSTANTIATIONS__INL