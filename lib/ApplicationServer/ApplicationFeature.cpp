////////////////////////////////////////////////////////////////////////////////
/// @brief application server feature
///
/// @file
///
/// DISCLAIMER
///
/// Copyright 2004-2012 triAGENS GmbH, Cologne, Germany
///
/// Licensed under the Apache License, Version 2.0 (the "License");
/// you may not use this file except in compliance with the License.
/// You may obtain a copy of the License at
///
///     http://www.apache.org/licenses/LICENSE-2.0
///
/// Unless required by applicable law or agreed to in writing, software
/// distributed under the License is distributed on an "AS IS" BASIS,
/// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
/// See the License for the specific language governing permissions and
/// limitations under the License.
///
/// Copyright holder is triAGENS GmbH, Cologne, Germany
///
/// @author Dr. Frank Celler
/// @author Copyright 2010-2012, triAGENS GmbH, Cologne, Germany
////////////////////////////////////////////////////////////////////////////////

#include "ApplicationFeature.h"

using namespace triagens::rest;
using namespace std;

// -----------------------------------------------------------------------------
// --SECTION--                                      constructors and destructors
// -----------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup ApplicationServer
/// @{
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
/// @brief constructor
////////////////////////////////////////////////////////////////////////////////

ApplicationFeature::ApplicationFeature (string const& name) 
  : _name(name) {
}

////////////////////////////////////////////////////////////////////////////////
/// @brief destructor
////////////////////////////////////////////////////////////////////////////////

ApplicationFeature::~ApplicationFeature () {
}

////////////////////////////////////////////////////////////////////////////////
/// @}
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// --SECTION--                                                    public methods
// -----------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup ApplicationServer
/// @{
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
/// @brief returns the name
////////////////////////////////////////////////////////////////////////////////

string const& ApplicationFeature::getName () const {
  return _name;
}

////////////////////////////////////////////////////////////////////////////////
/// @brief setups the options
////////////////////////////////////////////////////////////////////////////////

void ApplicationFeature::setupOptions (map<string, basics::ProgramOptionsDescription>&) {
}

////////////////////////////////////////////////////////////////////////////////
/// @brief parsing phase 1, before config file
////////////////////////////////////////////////////////////////////////////////

bool ApplicationFeature::parsePhase1 (basics::ProgramOptions&) {
  return true;
}

////////////////////////////////////////////////////////////////////////////////
/// @brief parsing phase 2, after config file
////////////////////////////////////////////////////////////////////////////////

bool ApplicationFeature::parsePhase2 (basics::ProgramOptions&) {
  return true;
}

////////////////////////////////////////////////////////////////////////////////
/// @brief prepares the feature
////////////////////////////////////////////////////////////////////////////////

bool ApplicationFeature::prepare () {
  return true;
}

////////////////////////////////////////////////////////////////////////////////
/// @brief checks if the feature is startable
////////////////////////////////////////////////////////////////////////////////

bool ApplicationFeature::isStartable () {
  return false;
}

////////////////////////////////////////////////////////////////////////////////
/// @brief starts the feature
////////////////////////////////////////////////////////////////////////////////

bool ApplicationFeature::start () {
  return false;
}

////////////////////////////////////////////////////////////////////////////////
/// @brief checks if the feature has been initialized
///
/// @note If the features has been started successfully but has already been
///       shut down, the method still returns @LIT{true}.
////////////////////////////////////////////////////////////////////////////////

bool ApplicationFeature::isStarted () {
  return false;
}

////////////////////////////////////////////////////////////////////////////////
/// @brief opens the feature for business
////////////////////////////////////////////////////////////////////////////////

bool ApplicationFeature::open () {
  return true;
}

////////////////////////////////////////////////////////////////////////////////
/// @brief checks if the feature is still running
////////////////////////////////////////////////////////////////////////////////

bool ApplicationFeature::isRunning () {
  return false;
}

////////////////////////////////////////////////////////////////////////////////
/// @brief begins the shut down sequence
////////////////////////////////////////////////////////////////////////////////

void ApplicationFeature::beginShutdown () {
}

////////////////////////////////////////////////////////////////////////////////
/// @brief shuts down everything
////////////////////////////////////////////////////////////////////////////////

void ApplicationFeature::shutdown () {
}

////////////////////////////////////////////////////////////////////////////////
/// @}
////////////////////////////////////////////////////////////////////////////////

// Local Variables:
// mode: outline-minor
// outline-regexp: "^\\(/// @brief\\|/// {@inheritDoc}\\|/// @addtogroup\\|/// @page\\|// --SECTION--\\|/// @\\}\\)"
// End:
