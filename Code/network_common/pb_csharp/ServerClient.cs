// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: server_client.proto
#pragma warning disable 1591, 0612, 3021
#region Designer generated code

using pb = global::Google.Protobuf;
using pbc = global::Google.Protobuf.Collections;
using pbr = global::Google.Protobuf.Reflection;
using scg = global::System.Collections.Generic;
namespace PS2C {

  /// <summary>Holder for reflection information generated from server_client.proto</summary>
  public static partial class ServerClientReflection {

    #region Descriptor
    /// <summary>File descriptor for server_client.proto</summary>
    public static pbr::FileDescriptor Descriptor {
      get { return descriptor; }
    }
    private static pbr::FileDescriptor descriptor;

    static ServerClientReflection() {
      byte[] descriptorData = global::System.Convert.FromBase64String(
          string.Concat(
            "ChNzZXJ2ZXJfY2xpZW50LnByb3RvEgRQUzJDGgxjb21tb24ucHJvdG8iFwoE",
            "Q2hhdBIPCgdtZXNzYWdlGAEgASgJIhsKBEF1dGgSEwoLYXV0aF9yZXN1bHQY",
            "ASABKAlQAGIGcHJvdG8z"));
      descriptor = pbr::FileDescriptor.FromGeneratedCode(descriptorData,
          new pbr::FileDescriptor[] { global::CommonReflection.Descriptor, },
          new pbr::GeneratedClrTypeInfo(null, new pbr::GeneratedClrTypeInfo[] {
            new pbr::GeneratedClrTypeInfo(typeof(global::PS2C.Chat), global::PS2C.Chat.Parser, new[]{ "Message" }, null, null, null),
            new pbr::GeneratedClrTypeInfo(typeof(global::PS2C.Auth), global::PS2C.Auth.Parser, new[]{ "AuthResult" }, null, null, null)
          }));
    }
    #endregion

  }
  #region Messages
  public sealed partial class Chat : pb::IMessage<Chat> {
    private static readonly pb::MessageParser<Chat> _parser = new pb::MessageParser<Chat>(() => new Chat());
    [global::System.Diagnostics.DebuggerNonUserCodeAttribute]
    public static pb::MessageParser<Chat> Parser { get { return _parser; } }

    [global::System.Diagnostics.DebuggerNonUserCodeAttribute]
    public static pbr::MessageDescriptor Descriptor {
      get { return global::PS2C.ServerClientReflection.Descriptor.MessageTypes[0]; }
    }

    [global::System.Diagnostics.DebuggerNonUserCodeAttribute]
    pbr::MessageDescriptor pb::IMessage.Descriptor {
      get { return Descriptor; }
    }

    [global::System.Diagnostics.DebuggerNonUserCodeAttribute]
    public Chat() {
      OnConstruction();
    }

    partial void OnConstruction();

    [global::System.Diagnostics.DebuggerNonUserCodeAttribute]
    public Chat(Chat other) : this() {
      message_ = other.message_;
    }

    [global::System.Diagnostics.DebuggerNonUserCodeAttribute]
    public Chat Clone() {
      return new Chat(this);
    }

    /// <summary>Field number for the "message" field.</summary>
    public const int MessageFieldNumber = 1;
    private string message_ = "";
    [global::System.Diagnostics.DebuggerNonUserCodeAttribute]
    public string Message {
      get { return message_; }
      set {
        message_ = pb::ProtoPreconditions.CheckNotNull(value, "value");
      }
    }

    [global::System.Diagnostics.DebuggerNonUserCodeAttribute]
    public override bool Equals(object other) {
      return Equals(other as Chat);
    }

    [global::System.Diagnostics.DebuggerNonUserCodeAttribute]
    public bool Equals(Chat other) {
      if (ReferenceEquals(other, null)) {
        return false;
      }
      if (ReferenceEquals(other, this)) {
        return true;
      }
      if (Message != other.Message) return false;
      return true;
    }

    [global::System.Diagnostics.DebuggerNonUserCodeAttribute]
    public override int GetHashCode() {
      int hash = 1;
      if (Message.Length != 0) hash ^= Message.GetHashCode();
      return hash;
    }

    [global::System.Diagnostics.DebuggerNonUserCodeAttribute]
    public override string ToString() {
      return pb::JsonFormatter.ToDiagnosticString(this);
    }

    [global::System.Diagnostics.DebuggerNonUserCodeAttribute]
    public void WriteTo(pb::CodedOutputStream output) {
      if (Message.Length != 0) {
        output.WriteRawTag(10);
        output.WriteString(Message);
      }
    }

    [global::System.Diagnostics.DebuggerNonUserCodeAttribute]
    public int CalculateSize() {
      int size = 0;
      if (Message.Length != 0) {
        size += 1 + pb::CodedOutputStream.ComputeStringSize(Message);
      }
      return size;
    }

    [global::System.Diagnostics.DebuggerNonUserCodeAttribute]
    public void MergeFrom(Chat other) {
      if (other == null) {
        return;
      }
      if (other.Message.Length != 0) {
        Message = other.Message;
      }
    }

    [global::System.Diagnostics.DebuggerNonUserCodeAttribute]
    public void MergeFrom(pb::CodedInputStream input) {
      uint tag;
      while ((tag = input.ReadTag()) != 0) {
        switch(tag) {
          default:
            input.SkipLastField();
            break;
          case 10: {
            Message = input.ReadString();
            break;
          }
        }
      }
    }

  }

  public sealed partial class Auth : pb::IMessage<Auth> {
    private static readonly pb::MessageParser<Auth> _parser = new pb::MessageParser<Auth>(() => new Auth());
    [global::System.Diagnostics.DebuggerNonUserCodeAttribute]
    public static pb::MessageParser<Auth> Parser { get { return _parser; } }

    [global::System.Diagnostics.DebuggerNonUserCodeAttribute]
    public static pbr::MessageDescriptor Descriptor {
      get { return global::PS2C.ServerClientReflection.Descriptor.MessageTypes[1]; }
    }

    [global::System.Diagnostics.DebuggerNonUserCodeAttribute]
    pbr::MessageDescriptor pb::IMessage.Descriptor {
      get { return Descriptor; }
    }

    [global::System.Diagnostics.DebuggerNonUserCodeAttribute]
    public Auth() {
      OnConstruction();
    }

    partial void OnConstruction();

    [global::System.Diagnostics.DebuggerNonUserCodeAttribute]
    public Auth(Auth other) : this() {
      authResult_ = other.authResult_;
    }

    [global::System.Diagnostics.DebuggerNonUserCodeAttribute]
    public Auth Clone() {
      return new Auth(this);
    }

    /// <summary>Field number for the "auth_result" field.</summary>
    public const int AuthResultFieldNumber = 1;
    private string authResult_ = "";
    [global::System.Diagnostics.DebuggerNonUserCodeAttribute]
    public string AuthResult {
      get { return authResult_; }
      set {
        authResult_ = pb::ProtoPreconditions.CheckNotNull(value, "value");
      }
    }

    [global::System.Diagnostics.DebuggerNonUserCodeAttribute]
    public override bool Equals(object other) {
      return Equals(other as Auth);
    }

    [global::System.Diagnostics.DebuggerNonUserCodeAttribute]
    public bool Equals(Auth other) {
      if (ReferenceEquals(other, null)) {
        return false;
      }
      if (ReferenceEquals(other, this)) {
        return true;
      }
      if (AuthResult != other.AuthResult) return false;
      return true;
    }

    [global::System.Diagnostics.DebuggerNonUserCodeAttribute]
    public override int GetHashCode() {
      int hash = 1;
      if (AuthResult.Length != 0) hash ^= AuthResult.GetHashCode();
      return hash;
    }

    [global::System.Diagnostics.DebuggerNonUserCodeAttribute]
    public override string ToString() {
      return pb::JsonFormatter.ToDiagnosticString(this);
    }

    [global::System.Diagnostics.DebuggerNonUserCodeAttribute]
    public void WriteTo(pb::CodedOutputStream output) {
      if (AuthResult.Length != 0) {
        output.WriteRawTag(10);
        output.WriteString(AuthResult);
      }
    }

    [global::System.Diagnostics.DebuggerNonUserCodeAttribute]
    public int CalculateSize() {
      int size = 0;
      if (AuthResult.Length != 0) {
        size += 1 + pb::CodedOutputStream.ComputeStringSize(AuthResult);
      }
      return size;
    }

    [global::System.Diagnostics.DebuggerNonUserCodeAttribute]
    public void MergeFrom(Auth other) {
      if (other == null) {
        return;
      }
      if (other.AuthResult.Length != 0) {
        AuthResult = other.AuthResult;
      }
    }

    [global::System.Diagnostics.DebuggerNonUserCodeAttribute]
    public void MergeFrom(pb::CodedInputStream input) {
      uint tag;
      while ((tag = input.ReadTag()) != 0) {
        switch(tag) {
          default:
            input.SkipLastField();
            break;
          case 10: {
            AuthResult = input.ReadString();
            break;
          }
        }
      }
    }

  }

  #endregion

}

#endregion Designer generated code
