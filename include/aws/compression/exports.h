#ifndef AWS_COMPRESSION_EXPORTS_H
#define AWS_COMPRESSION_EXPORTS_H
/*
 * Copyright 2010-2018 Amazon.com, Inc. or its affiliates. All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License").
 * You may not use this file except in compliance with the License.
 * A copy of the License is located at
 *
 *  http://aws.amazon.com/apache2.0
 *
 * or in the "license" file accompanying this file. This file is distributed
 * on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either
 * express or implied. See the License for the specific language governing
 * permissions and limitations under the License.
 */
#if defined(USE_WINDOWS_DLL_SEMANTICS) || defined(WIN32)
#    ifdef AWS_COMPRESSION_USE_IMPORT_EXPORT
#        ifdef AWS_COMPRESSION_EXPORTS
#            define AWS_COMPRESSION_API __declspec(dllexport)
#        else
#            define AWS_COMPRESSION_API __declspec(dllimport)
#        endif /* AWS_COMPRESSION_EXPORTS */
#    else
#        define AWS_COMPRESSION_API
#    endif /* AWS_COMPRESSION_USE_IMPORT_EXPORT */

#else /* defined (USE_WINDOWS_DLL_SEMANTICS) || defined (WIN32) */
#    define AWS_COMPRESSION_API
#endif /* defined (USE_WINDOWS_DLL_SEMANTICS) || defined (WIN32) */

#endif /* AWS_COMPRESSION_EXPORTS_H */
