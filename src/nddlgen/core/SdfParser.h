/**
 * Copyright 2015 Christian Dreher (christian.dreher@student.kit.edu)
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

#ifndef CORE_SDFPARSER_H_
#define CORE_SDFPARSER_H_

#include <sdf/sdf.hh>

#include "nddlgen/model/Arm.h"

namespace nddlgen { namespace core
{

	class SdfParser
	{

		private:

			nddlgen::model::Arm* _armModel;

		public:

			SdfParser(nddlgen::model::Arm* armModel);
			virtual ~SdfParser();

			bool parseDataStructure(sdf::ElementPtr sdfRoot);

	};

}}

#endif