from rest_framework import serializers
from edrum_server_app.models import NoteFileModel

class NoteFileSerializer (serializers.HyperlinkedModelSerializer) :
    class Meta :
        model = NoteFileModel
        fields = ('server_id', 'name', 'artist', 'ID', 'date', 'song')
