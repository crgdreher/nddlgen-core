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

#ifndef NDDLGEN_EXCEPTIONS_OBJECTFACTORYNOTSETEXCEPTION_HPP_
#define NDDLGEN_EXCEPTIONS_OBJECTFACTORYNOTSETEXCEPTION_HPP_

#include <exception>

namespace nddlgen { namespace exceptions { class ObjectFactoryNotSetException; }}

class nddlgen::exceptions::ObjectFactoryNotSetException : public std::exception
{
	public:

		ObjectFactoryNotSetException() {}
		virtual ~ObjectFactoryNotSetException() throw (){}

		virtual const char* what() const throw()
		{
			return "An ObjectFactory (inherits AbstractObjectFactory) was not set.";
		}

};

#endif
