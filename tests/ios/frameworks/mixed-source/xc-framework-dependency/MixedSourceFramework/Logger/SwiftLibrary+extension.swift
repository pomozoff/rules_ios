import SwiftXCFramework

public extension Foo {
    static var aProperty: String { "hey there!" }
}

// This extension did not trigger any error because Bar does not subclass from NSObject
extension Bar {
}
