/*
* //******************************************************************
* //
* // Copyright 2016 Samsung Electronics All Rights Reserved.
* //
* //-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
* //
* // Licensed under the Apache License, Version 2.0 (the "License");
* // you may not use this file except in compliance with the License.
* // You may obtain a copy of the License at
* //
* //      http://www.apache.org/licenses/LICENSE-2.0
* //
* // Unless required by applicable law or agreed to in writing, software
* // distributed under the License is distributed on an "AS IS" BASIS,
* // WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* // See the License for the specific language governing permissions and
* // limitations under the License.
* //
* //-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
*/

#include "JniOcStack.h"
#include "OCCloudProvisioning.hpp"
#include "JniOcCloudResultListener.h"
#include "JniGetAclIdByDeviceListener.h"
#include <mutex>


using namespace OC;

#ifndef _Included_org_iotivity_base_OcCloudProvisioning
#define _Included_org_iotivity_base_OcCloudProvisioning
class JniOcCloudProvisioning
{
    public:
        JniOcCloudProvisioning(std::shared_ptr<OCCloudProvisioning> cloudObject);
        ~JniOcCloudProvisioning();

        static JniOcCloudProvisioning* getJniOcCloudProvisioningPtr(JNIEnv *env, jobject thiz);
        JniOcCloudResultListener* AddCloudResultListener(JNIEnv* env, jobject jListener);
        JniGetAclIdByDeviceListener* AddGetAclByDeviceListener(JNIEnv* env, jobject jListener);
        void  RemoveCloudResultListener(JNIEnv* env, jobject jListener);
        void RemoveGetAclByDeviceIdListener(JNIEnv*, jobject);

        OCStackResult requestCertificate(JNIEnv* env, jobject jListener);
        OCStackResult getAclIdByDevice(JNIEnv*, std::string, jobject);
        OCStackResult getIndividualAclInfo(JNIEnv*, jobject, std::string &);
        OCStackResult getCRL(JNIEnv* env, jobject jListener);
        OCStackResult postCRL(JNIEnv* env, const std::string& thisUpdate,
                                  const std::string& nextUpdate, const OCByteString *crl,
                                   const stringArray_t *serialNumbers, jobject jListener);

    private:
        std::map<jobject, std::pair<JniOcCloudResultListener*, int>> resultMap;
        std::map<jobject, std::pair<JniGetAclIdByDeviceListener*, int>> aclresultMap;
        std::mutex resultMapLock;
        std::mutex aclresultMapLock;
        std::shared_ptr<OCCloudProvisioning>m_sharedCloudObject;
};


/* DO NOT EDIT THIS FILE - it is machine generated */
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     org_iotivity_base_OcCloudProvisioning
 * Method:    requestCertificate
 * Signature: (Lorg/iotivity/base/OcCloudProvisioning/RequestCertificateListener;)V
 */
JNIEXPORT void JNICALL Java_org_iotivity_base_OcCloudProvisioning_requestCertificate
  (JNIEnv *, jobject, jobject);

/*
 * Class:     org_iotivity_base_OcCloudProvisioning
 * Method:    getAclIdByDevice
 * Signature: (Ljava/lang/String;Lorg/iotivity/base/OcCloudProvisioning/GetAclIdByDeviceListener;)V
 */
JNIEXPORT void JNICALL Java_org_iotivity_base_OcCloudProvisioning_getAclIdByDevice
  (JNIEnv *, jobject, jstring, jobject);

/*
 * Class:     org_iotivity_base_OcCloudProvisioning
 * Method:    getIndividualAclInfo
 * Signature: (Ljava/lang/String;Lorg/iotivity/base/OcCloudProvisioning/GetIndividualAclInfoListener;)V
 */
JNIEXPORT void JNICALL Java_org_iotivity_base_OcCloudProvisioning_getIndividualAclInfo
  (JNIEnv *, jobject, jstring, jobject);

/*
 * Class:     org_iotivity_base_OcCloudProvisioning
 * Method:    getCRL
 * Signature: (Lorg/iotivity/base/OcCloudProvisioning/GetCRLListener;)V
 */
JNIEXPORT void JNICALL Java_org_iotivity_base_OcCloudProvisioning_getCRL
  (JNIEnv *, jobject, jobject);

/*
 * Class:     org_iotivity_base_OcCloudProvisioning
 * Method:    postCRL0
 * Signature: (Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/util/ArrayList;Lorg/iotivity/base/OcCloudProvisioning/PostCRLListener;)V
 */
JNIEXPORT void JNICALL Java_org_iotivity_base_OcCloudProvisioning_postCRL0
  (JNIEnv *, jobject, jstring, jstring, jstring, jobjectArray, jobject);

#ifdef __cplusplus
}
#endif
#endif
