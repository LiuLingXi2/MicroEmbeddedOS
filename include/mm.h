/**
 * @copyright
 * @brief define some nomal macro for test
 * @author 2226958871@qq.com
 */

#ifndef __INCLUDE_MM_H___
#define __INCLUDE_MM_H___

#define PAGE_SHIFT	 		12
#define TABLE_SHIFT 			9
#define SECTION_SHIFT			(PAGE_SHIFT + TABLE_SHIFT)

#define PAGE_SIZE   			(1 << PAGE_SHIFT)	
#define SECTION_SIZE			(1 << SECTION_SHIFT)	

#define LOW_MEMORY              	(2 * SECTION_SIZE) // 4MB

#endif // !__INCLUDE_MM_H___