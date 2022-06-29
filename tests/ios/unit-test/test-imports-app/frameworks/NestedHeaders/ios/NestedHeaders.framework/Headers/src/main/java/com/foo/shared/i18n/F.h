// //
// //  Generated by the J2ObjC translator.  DO NOT EDIT!
// //  source: src/main/java/com/squareup/shared/i18n/KeyManifest.java
// //

// #include <J2objcRuntime/J2ObjC_header.h>

// #pragma push_macro("INCLUDE_ALL_SrcMainJavaComSquareupSharedI18nKeyManifest")
// #ifdef RESTRICT_SrcMainJavaComSquareupSharedI18nKeyManifest
// #define INCLUDE_ALL_SrcMainJavaComSquareupSharedI18nKeyManifest 0
// #else
// #define INCLUDE_ALL_SrcMainJavaComSquareupSharedI18nKeyManifest 1
// #endif
// #undef RESTRICT_SrcMainJavaComSquareupSharedI18nKeyManifest

// #if __has_feature(nullability)
// #pragma clang diagnostic push
// #pragma GCC diagnostic ignored "-Wnullability-completeness"
// #endif

// #if !defined (ComSquareupSharedI18nKeyManifest_) && (INCLUDE_ALL_SrcMainJavaComSquareupSharedI18nKeyManifest || defined(INCLUDE_ComSquareupSharedI18nKeyManifest))
// #define ComSquareupSharedI18nKeyManifest_

// @class IOSClass;
// @protocol JavaUtilList;

// /*!
//  @brief The parent class for storing Key objects for each crossplatform project.
//  */
// @interface ComSquareupSharedI18nKeyManifest : NSObject

// #pragma mark Public

// - (instancetype __nonnull)init;

// /*!
//  @brief Uses reflection to enumerate every statically-declared Key
//  @param type A subclass of KeyManifest for each crossplatform project that uses localization
//  @return A list of all Keys associated with a KeyManifest subclass
//  @throw IllegalAccessException
//  */
// + (id<JavaUtilList>)keysWithIOSClass:(IOSClass *)type;

// @end

// J2OBJC_EMPTY_STATIC_INIT(ComSquareupSharedI18nKeyManifest)

// FOUNDATION_EXPORT void ComSquareupSharedI18nKeyManifest_init(ComSquareupSharedI18nKeyManifest *self);

// FOUNDATION_EXPORT id<JavaUtilList> ComSquareupSharedI18nKeyManifest_keysWithIOSClass_(IOSClass *type);

// J2OBJC_TYPE_LITERAL_HEADER(ComSquareupSharedI18nKeyManifest)

// #endif


// #if __has_feature(nullability)
// #pragma clang diagnostic pop
// #endif
// #pragma pop_macro("INCLUDE_ALL_SrcMainJavaComSquareupSharedI18nKeyManifest")
