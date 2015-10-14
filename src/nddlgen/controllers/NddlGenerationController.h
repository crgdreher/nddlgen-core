/**
 * Copyright 2015 Christian Dreher (dreher@charlydelta.org)
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

#ifndef NDDLGEN_CONTROLLER_NDDLGENERATIONCONTROLLER_H_
#define NDDLGEN_CONTROLLER_NDDLGENERATIONCONTROLLER_H_

#include <iostream>
#include <fstream>
#include <string>

#include <boost/algorithm/string.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

#include <nddlgen/exceptions/FileAlreadyExistsException.hpp>
#include <nddlgen/models/DomainDescriptionModel.h>
#include <nddlgen/utilities/WorkflowControllerConfig.h>
#include <nddlgen/utilities/Meta.h>

namespace nddlgen { namespace controllers { class NddlGenerationController; }}

class nddlgen::controllers::NddlGenerationController
{

	private:

		static std::string getPrettifiedDate();

		NddlGenerationController();
		virtual ~NddlGenerationController();

	public:

		static void writeModelFile(nddlgen::models::DomainDescriptionModel* domainDescription,
				nddlgen::utilities::WorkflowControllerConfig* controllerConfig,
				bool forceOverwrite);
		static void writeInitialStateFile(nddlgen::models::DomainDescriptionModel* domainDescription,
				nddlgen::utilities::WorkflowControllerConfig* controllerConfig,
				bool forceOverwrite);

};

#endif
