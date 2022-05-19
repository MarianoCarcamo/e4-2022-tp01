#ifndef UNITTEST_TRANSPORT_H
#define UNITTEST_TRANSPORT_H

#ifdef __cplusplus
    extern "C"{
#endif

void unityOutputStart(void);
void unityOutputChar(char c);
void unityOutputFlush(void);
void unityOutputComplete(void);

#define UNITY_OUTPUT_START() unityOutputStart()
#define UNITY_OUTPUT_CHAR(c) unityOutputChar(c)
#define UNITY_OUTPUT_FLUSH() unityOutputFlush()
#define UNITY_OUTPUT_COMPLETE() unityOutputComplete()

#ifdef __cplusplus
    }
#endif

#endif
