// Copyright 2015 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef GlobalBullet_h
#define GlobalBullet_h

namespace blink {

class Bullet;
class DOMWindow;
class WorkerGlobalScope;

class GlobalBullet {
public:
    static Bullet* bullet(DOMWindow&);
    static Bullet* bullet(WorkerGlobalScope&);
};

} // namespace blink

#endif // GlobalBullet_h
