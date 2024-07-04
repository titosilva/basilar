#pragma once

#define AllowInternalTestFor(class_name) friend class FriendTest<class_name>

template<class T>
class FriendTest {
};
