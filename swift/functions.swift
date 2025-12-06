//
//  functions.swift
//
//  Created by Anthony Sainez on 13 March 2019.
//  Copyright © 2020 Anthony Sainez. All rights reserved.
//

import Foundation

/// Creates a list of integers within a specified range.
///
/// - Parameters:
///   - start: The starting integer of the range.
///   - end: The ending integer of the range.
/// - Returns: An array of integers from `start` to `end`, inclusive.
func list(from start: Int, to end: Int) -> [Int] {
    var list = [Int]()
    
    let range = CountableRange(start...end)
    
    for index in range {
        list.append(index)
    }
    
    return list
    
}

/// Creates a list of odd integers within a specified range.
///
/// - Parameters:
///   - start: The starting integer of the range.
///   - end: The ending integer of the range.
/// - Returns: An array of odd integers from `start` to `end`, inclusive.
func odd(from start: Int, to end: Int) -> [Int] {
    return (start...end).filter{$0 % 2 == 1}
}

/// Creates a list of alternating odd integers from a range.
///
/// This function first generates all odd numbers in the range, and then selects
/// every other odd number starting from the first one.
///
/// - Parameters:
///   - start: The starting integer of the range.
///   - end: The ending integer of the range.
/// - Returns: An array of alternating odd integers.
func alternatingOdd(from start: Int, to end: Int) -> [Int] {
    let list = odd(from: start, to: end)
    return list.filter{list.index(of: $0)! % 2 == 0}
}
