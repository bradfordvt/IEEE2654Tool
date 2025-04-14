/*
 *    ModelData.cpp
 *
 *    Class to implement the global data for the model element.
 *
 *    Class to implement the global data for the model element.
 * 
 * Copyright (C) 2024 Bradford G. Van Treuren
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

static const char __authors__[] = "Bradford G. Van Treuren";
static const char __contact__[] = "bradvt59@gmail.com";
static const char __copyright__[] = "Copyright (C) 2024, Bradford G. Van Treuren";
static const char __credits__[] = "Bradford G. Van Treuren";
static const char __date__[] = "2024/07/29";
static bool __deprecated__ = false;
static const char __email__[] = "bradvt59@gmail.com";
static const char __license__[] = "Apache-2.0";
static const char __maintainer__[] = "Bradford G. Van Treuren";
static const char __status__[] = "Alpha/Experimental";
static const char __version__[] = "0.0.1";

const char* translator_error_strings[] = {
		"No error!",
		"The Metaname provided is not known!",
		"The host of this translator encountered an error.",
		"The driver for this branch encountered an error.",
		"The format of the message was wrong.",
		"The format is not a JSON format.",
		"There is a required attribute missing.",
		"An invalid attribute was detected."
		"There is a required parameter missing.",
		"An inverted parameter was detected.",
		"Memory could not be allocated.",
		"An unknown error was detected."
};

const char* translator_status_strings[] = {
		"OK",
		"PROCESSING",
		"WAITING",
		"UNRECOVERABLE",
		"FAILURE"
};

const char** get_translator_error_strings_data() {
	return &translator_error_strings[0];
}

const char** get_translator_status_strings_data() {
	return &translator_status_strings[0];
}
