#ifndef __sitkTransform_h
#define __sitkTransform_h

#include "sitkCommon.h"
#include <vector>


namespace itk
{

// Forward decalaration for pointer
class TransformBase;
template< typename TScalar, unsigned int NDimension> class CompositeTransform;

namespace simple
{

class PimpleTransformBase;


enum TransformEnum { sitkIdentity,
                     sitkTranslation,
                     sitkScale,
                     sitkScaleLogarithmic,
                     sitkQuaternionRigid,
                     sitkVersor,
                     sitkAffine,
                     sitkComposite };


class SITKCommon_EXPORT Transform
{
public:
  typedef Transform Self;

  /** By default a 3-d identity transform is constructed
   */
  Transform( void );
  template<unsigned int NDimension>
  explicit Transform( itk::CompositeTransform< double, NDimension >* compositeTransform )
    {
      sitkStaticAssert( NDimension == 2 | NDimension == 3, "Only 2D and 3D transforms are supported" );
      if ( compositeTransform == NULL )
        {
        sitkExceptionMacro( "Unable to construct a null transform!" );
        }
      this->InternalInitialization<NDimension>( sitkComposite, compositeTransform );
    }
  Transform( unsigned int dimensions, TransformEnum type);
  virtual ~Transform( void );

  //
  Transform &operator=( const Transform & );
  Transform( const Transform & );


  itk::TransformBase* GetITKBase( void );
  const itk::TransformBase* GetITKBase( void ) const;

  unsigned int GetDimension( void ) const;

  /** Set/Get Parameter
   */
  void SetParameters ( const std::vector<double>& parameters );
  std::vector<double> GetParameters( void ) const ;

  Transform &AddTransform( Transform &t );

  // read
  static Transform ReadTransform( const std::string &filename );

  // write
  void WriteTransform( const std::string &filename ) const;
  static void WriteTransform( const Transform &transform, const std::string &filename);

  // set identity

  std::string ToString( void ) const;


protected:

  void MakeUniqueForWrite( void );

private:

  template< unsigned int VDimension>
  void InternalInitialization(  TransformEnum type, itk::TransformBase *base = NULL );

  // As is the architecture of all SimpleITK pimples,
  // this pointer should never be null and should always point to a
  // valid object
  PimpleTransformBase *m_PimpleTransform;
};
}
}

#endif // __sitkTransform_h
