//
//  functions.swift
//
//  Created by Anthony Sainez on 3/13/19.
//  Copyright © 2019 Anthony Sainez. All rights reserved.
//

import Foundation

func list(from start: Int, to end: Int) -> [Int] {
    var list = [Int]()
    
    let range = CountableRange(start...end)
    
    for index in range {
        list.append(index)
    }
    
    return list
    
}

func odd(from start: Int, to end: Int) -> [Int] {
    return (start...end).filter{$0 % 2 == 1}
}

func alternatingOdd(from start: Int, to end: Int) -> [Int] {
    let list = odd(from: start, to: end)
    return list.filter{list.index(of: $0)! % 2 == 0}
}
