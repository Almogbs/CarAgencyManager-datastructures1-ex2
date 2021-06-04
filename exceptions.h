#ifndef EXCEPTIONS_H_
#define EXCEPTIONS_H_

/**
* Exception List
*
* an Exception List for DataStructures namespace.
*
*/

#include <stdexcept>

namespace DataStructures{

	class AllocationError : public std::exception {};
	class InvalidArg : public std::exception {};
	class NodeExist : public std::exception {};
	class NodeNotExist : public std::exception {};
	class Failure : public std::exception {};
	class Assert : public std::exception {};
}

#endif  /* EXCEPTIONS_H_ */
