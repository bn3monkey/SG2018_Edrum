from rest_framework import serializers
from edrum_server_app.models import NoteFileModel, User

class NoteFileSerializer (serializers.HyperlinkedModelSerializer) :
    class Meta :
        model = NoteFileModel
        fields = ('server_id', 'name', 'artist', 'ID', 'date', 'song')

class UserSerializer(serializers.HyperlinkedModelSerializer):
    class Meta:
        model = User
        fields = ('user_id','password','is_active','is_admin')
        extra_kwargs = {'password' : {'write_only' : True},}
    
    def create(self,validated_data):
        password = validated_data.pop('password',None)
        instance = self.Meta.model(**validated_data)
        if password is not None:
            instance.set_password(password)
        instance.save()
        return instance

class LoginSerializer(serializers.HyperlinkedModelSerializer):
    class Meta:
        model = User
        fields = ('user_id','password')
        exclude = ('is_active','is_admin')    

class SignUpSerializer(serializers.HyperlinkedModelSerializer):
    class Meta:
        model = User
        fields = ('user_id','password')
        extra_kwargs = {'password':{'write_only':True},}

    def create(self,validated_data):
        password = validated_data.pop('password',None)
        instance = self.Meta.model(**validated_data)
        if password is not None:
            instance.set_password(password)
        instance.save()
        return instance

class RedundantSerializer(serializers.HyperlinkedModelSerializer):
    class Meta:
        model = User
        fields = ('user_id')

    def update(self,instance,validated_data):
        instance.user_id = validated_data.get('user_id',instance.user_id)
        return instance
