/*
 * CoordinatedState.h
 *
 * This source file is part of the FoundationDB open source project
 *
 * Copyright 2013-2018 Apple Inc. and the FoundationDB project authors
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef FDBSERVER_COORDINATED_STATE_H
#define FDBSERVER_COORDINATED_STATE_H
#pragma once

#include "fdbclient/FDBTypes.h"

class MovableCoordinatedState : NonCopyable {
public:
	MovableCoordinatedState( class ServerCoordinators const& );
	void operator=(MovableCoordinatedState&& av);
	~MovableCoordinatedState();

	Future<Value> read();

	Future<Void> onConflict();

	Future<Void> setExclusive(Value v);

	Future<Void> move( class ClusterConnectionString const& nc );
	// Call only after setExclusive returns.  Attempts to move the coordinated state
	// permanently to the new ServerCoordinators, which must be uninitialized.  Returns when the process has
	// reached the point where a leader elected by the new coordinators should be doing the rest of the work
	// (and therefore the caller should die).

private:
	struct MovableCoordinatedStateImpl *impl;
};

#endif
