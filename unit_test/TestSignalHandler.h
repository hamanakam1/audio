/******************************************************************************
 * Copyright 2013, doubleTwist Corporation and Qualcomm Innovation Center, Inc.
 *
 *    All rights reserved.
 *    This file is licensed under the 3-clause BSD license in the NOTICE.txt
 *    file for this project. A copy of the 3-clause BSD license is found at:
 *
 *        http://opensource.org/licenses/BSD-3-Clause.
 *
 *    Unless required by applicable law or agreed to in writing, software
 *    distributed under the license is distributed on an "AS IS" BASIS,
 *    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *    See the license for the specific language governing permissions and
 *    limitations under the license.
 ******************************************************************************/

#include <alljoyn/BusAttachment.h>
#include <alljoyn/Status.h>
#include <qcc/Event.h>
#include <vector>

using namespace std;
using namespace qcc;
using namespace ajn;

class TestSignalHandler : public BusObject {

  private:
    BusAttachment* mBus;
    vector<const char*> mMatches;
    Event* mReadyToEmitEvent;
    Event* mPlayStateChangedEvent;
    Event* mFifoPositionChangedEvent;
    Event* mMuteChangedEvent;
    Event* mVolumeChangedEvent;
    Event* mOwnershipLostEvent;
    const InterfaceDescription::Member* mAudioDataMember;
    const InterfaceDescription::Member* mImageDataMember;
    const InterfaceDescription::Member* mMetaDataMember;
    uint8_t mPlayState;
    bool mMute;
    int16_t mVolume;
    String mNewOwner;
    SessionId mSessionId;
    const char* mPortPath;

  public:
    TestSignalHandler(BusAttachment* bus, const char* path, SessionId sessionId);
    ~TestSignalHandler();

    void RegisterHandlers();
    void ObjectRegistered();
    void ObjectUnregistered();
    void FifoPositionChangedSignalHandler(const InterfaceDescription::Member* member, const char* sourcePath, Message& msg);
    void PlayStateChangedSignalHandler(const InterfaceDescription::Member* member, const char* sourcePath, Message& msg);
    void MuteChangedSignalHandler(const InterfaceDescription::Member* member, const char* sourcePath, Message& msg);
    void VolumeChangedSignalHandler(const InterfaceDescription::Member* member, const char* sourcePath, Message& msg);
    void OwnershipLostSignalHandler(const InterfaceDescription::Member* member, const char* sourcePath, Message& msg);
    uint8_t GetPlayState();
    bool GetMute();
    int16_t GetVolume();
    const char* GetNewOwner();
    QStatus WaitUntilReadyToEmit(uint32_t waitMs);
    QStatus WaitForPlayStateChanged(uint32_t waitMs);
    QStatus WaitForFifoPositionChanged(uint32_t waitMs);
    QStatus WaitForMuteChanged(uint32_t waitMs);
    QStatus WaitForVolumeChanged(uint32_t waitMs);
    QStatus WaitForOwnershipLost(uint32_t waitMs);
    QStatus EmitAudioDataSignal(uint8_t* data, int32_t dataSize, uint64_t timestamp);
    QStatus EmitImageDataSignal(uint8_t* data, int32_t dataSize);
    QStatus EmitMetaDataSignal(MsgArg* metadata);
};
