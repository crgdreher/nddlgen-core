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

#ifndef NDDLGEN_CONTROLLER_ISDPARSER_H_
#define NDDLGEN_CONTROLLER_ISDPARSER_H_

#include <cstddef>

#include <tinyxml.h>

#include <nddlgen/utilities/Types.hpp>

namespace nddlgen { namespace controller
{

	class IsdParser
	{

		private:

			IsdParser();
			virtual ~IsdParser();

		public:

			static nddlgen::types::IsdRoot parseIsd(std::string filename);

	};

}}

#endif
